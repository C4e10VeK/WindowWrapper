#ifndef EVENT_HPP
#define EVENT_HPP

#include <vector>
#include <memory>
#include <cassert>
#include <algorithm>

namespace winWrap
{
	template <typename... Args> class AbstractEventHandler
	{
	public:
		AbstractEventHandler() = default;
		virtual ~AbstractEventHandler() = default;
		virtual void call(Args... args) = 0;

		bool operator==(const AbstractEventHandler<Args...> &o) const { return isEqual(o); }

		bool operator!=(const AbstractEventHandler<Args...> &o) const { return *this != o; }

	protected:
		virtual bool isEqual(const AbstractEventHandler<Args...> &o) const = 0;
	};

	template <typename... Args> class FunctionEventHandler : public AbstractEventHandler<Args...>
	{
	private:
		using function = void (*)(Args...);

		function m_func;

	public:
		explicit FunctionEventHandler(function f) : AbstractEventHandler<Args...>(), m_func(f) { assert(f); }

		void call(Args... args) override { m_func(std::forward<Args>(args)...); }

	protected:
		bool isEqual(const AbstractEventHandler<Args...> &o) const override
		{
			const auto *other = dynamic_cast<const FunctionEventHandler<Args...> *>(&o);
			return (other != nullptr && other->m_func == m_func);
		}
	};

	template <class C, typename... Args> class MethodEventHandler : public AbstractEventHandler<Args...>
	{
	private:
		using Method = void (C::*)(Args...);

		C &m_class;
		Method m_method;

	public:
		MethodEventHandler(C &c, Method m) : AbstractEventHandler<Args...>(), m_class(c), m_method(m) { assert(m); }

		void call(Args... args) override { (m_class.*m_method)(std::forward<Args>(args)...); }

	protected:
		bool isEqual(const AbstractEventHandler<Args...> &o) const override
		{
			const auto *other = dynamic_cast<const MethodEventHandler<C, Args...> *>(&o);
			return (other != nullptr && &other->m_class == &m_class && other->m_method == m_method);
		}
	};

	template <typename... Args> class IEvent
	{
	public:
		virtual ~IEvent() = default;

		void operator+=(std::shared_ptr<AbstractEventHandler<Args...>> handler) { add(handler); }

		void operator-=(std::shared_ptr<AbstractEventHandler<Args...>> handler) { remove(handler); }

		void operator+=(void (*f)(Args...)) { add(f); }

		void operator-=(void (*f)(Args...)) { remove(f); }

	protected:
		virtual void add(std::shared_ptr<AbstractEventHandler<Args...>> &handler) = 0;
		virtual void remove(std::shared_ptr<AbstractEventHandler<Args...>> &handler) = 0;

		virtual void add(void (*f)(Args...)) = 0;
		virtual void remove(void (*f)(Args...)) = 0;
	};

	template <typename... Args> class Event : public IEvent<Args...>
	{
	private:
		using HandlerPtr = std::shared_ptr<AbstractEventHandler<Args...>>;
		class EventHandlerList
		{
		private:
			using HandlerIt = typename std::vector<HandlerPtr>::const_iterator;

			std::vector<HandlerPtr> m_handlers;

		public:
			EventHandlerList() : m_handlers() {}

			void add(HandlerPtr handler)
			{
				if (findHandler(handler) == m_handlers.end())
				{
					m_handlers.emplace_back(handler);
				}
			}

			void remove(HandlerPtr handler)
			{
				auto it = findHandler(handler);

				if (it != m_handlers.end())
				{
					m_handlers.erase(it);
				}
			}

			void call(Args... args)
			{
				for (auto &handle : m_handlers)
				{
					if (handle)
						handle->call(std::forward<Args>(args)...);
				}
			}

		private:
			inline HandlerIt findHandler(HandlerPtr &handler) const
			{
				return std::find_if(
					m_handlers.cbegin(), m_handlers.cend(), [&handler](const HandlerPtr oneHandler) { return (*oneHandler == *handler); });
			}
		};

		EventHandlerList m_handlerList;

	public:
		using IType = IEvent<Args...>;

		Event() : m_handlerList() {}

		void operator()(Args... args) { m_handlerList.call(std::forward<Args>(args)...); }

	protected:
		void add(HandlerPtr &handler) override { m_handlerList.add(handler); }

		void remove(HandlerPtr &handler) override { m_handlerList.remove(handler); }

		void add(void (*f)(Args...)) override { m_handlerList.add(std::make_shared<FunctionEventHandler<Args...>>(f)); }

		void remove(void (*f)(Args...)) override { m_handlerList.remove(std::make_shared<FunctionEventHandler<Args...>>(f)); }
	};

	template <class C, typename... Args>
	std::shared_ptr<MethodEventHandler<C, Args...>> createEventHandler(C &object, void (C::*method)(Args...))
	{
		return std::make_shared<MethodEventHandler<C, Args...>>(object, method);
	}
}
#endif