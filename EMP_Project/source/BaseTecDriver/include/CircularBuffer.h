/*
 * CircularBuffer.h
 *
 *  Created on: 10.06.2014
 *      Author: c.zeuke
 */

//Quelle: https://github.com/dhylands/TimerUART/blob/master/CBUF.h

#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_

template < class IndexType, unsigned Size, class EntryType >
class CircularBuffer
{
public:
	IndexType Len() const   { return m_putIdx - m_getIdx; }

	bool IsEmpty() const    { return Len() == 0; }
	bool IsFull() const     { return Len() == Size; }
	bool Error() const      { return Len() > Size; }

	void Push( EntryType val )
	{
		//m_entry[ m_putIdx++ & ( Size - 1 )] = val;
		m_entry[ m_putIdx++ ] = val;
		if (m_putIdx > Size - 1 ) m_putIdx = 0;
	}

	EntryType Pop()
	{
		EntryType retVal;
		//return m_entry[ m_getIdx++ & ( Size - 1 )];
		retVal = m_entry[ m_getIdx++];
		if (m_getIdx > Size - 1 ) m_getIdx = 0;
		return retVal;
	}

private:

	volatile IndexType  m_getIdx;
	volatile IndexType  m_putIdx;
	EntryType           m_entry[ Size ];

public:
	CircularBuffer()
	{
		m_getIdx = m_putIdx = 0;
	}
};

#endif /* CIRCULARBUFFER_H_ */
