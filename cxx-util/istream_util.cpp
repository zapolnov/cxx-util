/* vim: set ai noet ts=4 sw=4 tw=115: */
//
// Copyright (c) 2014 Nikolay Zapolnov (zapolnov@gmail.com).
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#include "istream_util.h"

size_t istream_read(std::istream & stream, void * buf, size_t size)
{
	char * p = reinterpret_cast<char *>(buf);
	size_t totalBytesRead = 0;

	do
	{
		if (stream.eof() || stream.bad() || stream.fail())
			break;

		stream.read(p, static_cast<std::streamsize>(size));
		size_t bytesRead = static_cast<size_t>(stream.gcount());

		totalBytesRead += bytesRead;
		p += bytesRead;
		size -= bytesRead;
	}
	while (size > 0);

	if (stream.eof())
		stream.clear(stream.rdstate() & ~(std::ios_base::badbit | std::ios_base::failbit));

	return totalBytesRead;
}
