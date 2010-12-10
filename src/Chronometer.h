/*
 *  Copyright (c) 2010
 *    Hugo Stefan Kaus Puhlmann <hugopuhlmann@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
*/

#ifndef RTY_CHRONOMETER_H
#define RTY_CHRONOMETER_H

#include <ctime>

namespace rty
{
	namespace detail
	{
		class MyTime
		{
		public:
			time_t m_time;

			inline MyTime(time_t& i)
				: m_time(i)
			{}

			inline operator time_t()
			{
				return m_time;
			}
		};
	}

	/*double operator-(detail::MyTime& i, detail::MyTime& j)
	{
		return difftime(i.m_time, j.m_time);	
	}*/

	class Chronometer
	{
	public:
		inline static Chronometer& getInstance();

		inline time_t getCurrent();
	private:
		Chronometer()
		{}

		static Chronometer instance;
	};

	Chronometer& Chronometer::getInstance()
	{
		return instance;
	}
	
	time_t Chronometer::getCurrent()
	{
		return time(0);
	}
}

/*double operator-(rty::detail::MyTime& i, rty::detail::MyTime& j)
{
	return difftime(i.m_time, j.m_time);	
}*/

#endif