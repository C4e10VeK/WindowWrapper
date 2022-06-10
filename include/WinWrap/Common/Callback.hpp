#pragma once

#include "Types.hpp"
#include <memory>
#include <cassert>

namespace winWrap
{
	template<typename... Args>
	class ICallbackHandler
	{
	public:
		virtual ~ICallbackHandler() = default;

		virtual void call(Args &&...args) = 0;
	};

	template<typename F, typename... Args>
	class FunctorCallbackHandler;

	template<typename F>
	class FunctorHolder
	{
	private:
		F &m_functor;

		template<typename T, typename... Args> friend class FunctorCallbackHandler;
	public:
		FunctorHolder(F &functor) : m_functor(functor) { }

		template<typename... Args>
		operator std::shared_ptr<ICallbackHandler<Args...>>()
		{
			return std::make_shared<FunctorCallbackHandler<F, Args...>>(m_functor);
		}
	};

	template<typename F, typename... Args>
	class FunctorCallbackHandler : public ICallbackHandler<Args...>
	{
	private:
		FunctorHolder<F> m_functorHolder;
	public:
		FunctorCallbackHandler(F &functor) : m_functorHolder(functor) { }

		void call(Args &&...args) override
		{
			m_functorHolder.m_functor(std::forward<Args>(args)...);
		}
	};

	template<typename C, typename... Args>
	class MethodCallbackHandler : public ICallbackHandler<Args...>
	{
	private:
		using Method = void (C::*)(Args...);
		
		C &m_class;
		Method m_method;
	public:
		MethodCallbackHandler(C &c, Method m) : m_class(c), m_method(m) {  }

		void call(Args &&...args) override
		{
			(m_class.*m_method)(std::forward<Args>(args)...);
		}
	};

	template<typename... Args>
	class ICallback
	{
		using CallbackPtr = std::shared_ptr<ICallbackHandler<Args...>>;
	public:
		virtual ~ICallback() = default;

		virtual void connect(CallbackPtr &&callback) = 0;

		template<typename T>
		ICallback &operator=(T &&some)
		{
			connect(static_cast<CallbackPtr>(some));
			return *this;
		}
	};

	template<typename... Args>
	class Callback : public ICallback<Args...>
	{
	private:
		using CallbackPtr = std::shared_ptr<ICallbackHandler<Args...>>;

		CallbackPtr m_callback;
	public:
		using IType = ICallback<Args...>;

		void call(Args &&...args)
		{
			if (m_callback == nullptr) return;
			m_callback->call(std::forward<Args>(args)...);
		}

		void connect(CallbackPtr &&some) override
		{
			m_callback = some;
		}

		void operator()(Args ...args)
		{
			call(std::forward<Args>(args)...);
		}
	};

	template<typename F>
	FunctorHolder<F> createCallback(F &&functor)
	{
		return FunctorHolder<F>(functor);
	}

	template<typename C, typename... Args>
	std::shared_ptr<ICallbackHandler<Args...>> createCallback(C &c, void(C::*method)(Args...))
	{
		return std::make_shared<MethodCallbackHandler<C, Args...>>(c, method);
	}
} // namespace winWrap
