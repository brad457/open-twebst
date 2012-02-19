/*
 * This file is part of Open Twebst - web automation framework.
 * Copyright (c) 2012 Adrian Dorache
 * adrian.dorache@codecentrix.com
 *
 * Open Twebst is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Open Twebst is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Open Twebst. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Twebst can be used under a commercial license if such has been acquired
 * (see http://www.codecentrix.com/). The commercial license does not
 * cover derived or ported versions created by third parties under GPL.
 */

#pragma once

const int SL_LOCKED   = 1;
const int SL_UNLOCKED = 0;


class SpinLock
{
public:
	explicit SpinLock(volatile long* pLock)
	{
		_ASSERTE(pLock != NULL);
		m_pLock = pLock;
	}

	~SpinLock()
	{
		m_pLock = NULL;
	}

	void Lock()
    {
        while (::InterlockedExchange(m_pLock, SL_LOCKED) != SL_UNLOCKED)
        {
			::Sleep(30);
        }
	}

	void Unlock()
    {
		_ASSERTE(HasLock());
		::InterlockedExchange(m_pLock, SL_UNLOCKED);
	}


private:
    SpinLock(const SpinLock &);
    SpinLock& operator=(const SpinLock &);

	BOOL HasLock() const
	{
		return (*m_pLock == SL_LOCKED);
	}


private:
	volatile long* m_pLock;
};
