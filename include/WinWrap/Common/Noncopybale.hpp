#pragma once

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

