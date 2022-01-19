#pragma once

#include <Common/Callback.hpp>
#include <Common/Types.hpp>
#include <memory>
#include <cassert>

namespace winWrap
{
	template<typename... Args>
	class AbstractCallback
	{
	public:
		virtual ~AbstractCallback() = default;

		virtual void call(Args... args) = 0;
	};

	template<typename F, typename... Args>
	class FunctorCallback;

	template<typename F>
	class FunctorHolder
	{
	private:
		F &m_functor;

		template<typename T, typename... Args> friend class FunctorCallback;
	public:
		FunctorHolder(F &functor) : m_functor(functor) { }

		template<typename... Args>
		operator std::shared_ptr<AbstractCallback<Args...>>()
		{
			return std::make_shared<FunctorCallback<F, Args...>>(m_functor);
		}
	};

	template<typename F, typename... Args>
	class FunctorCallback : public AbstractCallback<Args...>
	{
	private:
		FunctorHolder<F> m_functorHolder;
	public:
		FunctorCallback(F &functor) : m_functorHolder(functor) { }

		void call(Args... args) override
		{
			m_functorHolder.m_functor(std::forward<Args>(args)...);
		}
	};

	template<typename C, typename... Args>
	class MethodCallback : public AbstractCallback<Args...>
	{
	private:
		using Method = void (C::*)(Args...);
		
		C &m_class;
		Method m_method;
	public:
		MethodCallback(C &c, Method m) : m_class(c), m_method(m) {  }

		void call(Args... args) override
		{
			(m_class.*m_method)(std::forward<Args>(args)...);
		}
	};

	template<typename... Args>
	class ICallback
	{
		using CallbackPtr = std::shared_ptr<AbstractCallback<Args...>>;
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
		using CallbackPtr = std::shared_ptr<AbstractCallback<Args...>>;

		CallbackPtr m_callback;
	public:
		using IType = ICallback<Args...>;

		void call(Args... args)
		{
			if (m_callback == nullptr) return;
			m_callback->call(std::forward<Args>(args)...);
		}

		void connect(CallbackPtr &&some) override
		{
			m_callback = some;
		}

		void operator()(Args... args)
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
	std::shared_ptr<AbstractCallback<Args...>> createCallback(C &c, void(C::*method)(Args...))
	{
		return std::make_shared<MethodCallback<C, Args...>>(c, method);
	}
} // namespace winWrap
