#ifndef WINDOWWRAPPER_NONCOPYBALE_HPP
#define WINDOWWRAPPER_NONCOPYBALE_HPP

namespace winWrap
{
	class noncopybale
	{
	public:
		noncopybale() = default;
		~noncopybale() = default;

	private:
		noncopybale(const noncopybale&) = delete;
		noncopybale &operator=(const noncopybale&) = delete;
	};
}

#endif // WINDOWWRAPPER_NONCOPYBALE_HPP
