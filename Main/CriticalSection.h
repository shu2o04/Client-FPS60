#pragma once
#if(MAIN_VERSION_S8)

class CCriticalSection
{
	public:
	CCriticalSection();
	virtual ~CCriticalSection();
	void lock();
	void unlock();
	private:
	CRITICAL_SECTION m_critical;
};
#endif