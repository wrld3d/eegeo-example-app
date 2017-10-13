// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <android/log.h>
#include <assert.h>
#include <csignal>
#include <pthread.h>
#include "Types.h"
#include "AndroidAppThreadAssertions.h"

namespace
{
    class AndroidAppThreadIdentifier
    {
        pthread_t m_nativeThreadId;
        pthread_t m_uiThreadId;
        bool m_hasSetNativeThreadId;
        bool m_hasSetUiThreadId;

        void AssertWithLogAndBreak(bool condition, const char* message, const char* file, int line)
        {
            if(!condition)
            {
                __android_log_print(ANDROID_LOG_INFO,"Eegeo_Examples","ASSERT: %s at %s (%d).\n", message, file, line);

#ifdef NDEBUG
                raise(SIGABRT);
#else
                assert(false);
#endif
            }
        }

    public:
        AndroidAppThreadIdentifier()
            : m_nativeThreadId()
            , m_uiThreadId()
            , m_hasSetNativeThreadId(false)
            , m_hasSetUiThreadId(false)
        {

        }

        void NominateCurrentlyRunningThreadAsUiThread()
        {
            Eegeo_ASSERT(!m_hasSetUiThreadId, "Can only nominate UI thread once.\n");
            m_uiThreadId = pthread_self();
            m_hasSetUiThreadId = true;
        }

        void AssertCurrentlyRunningOnNominatedUiThread(const char* file, int line)
        {
            Eegeo_ASSERT(m_hasSetUiThreadId, "UI thread has not yet been nominated.\n");
            const pthread_t currentThreadId(pthread_self());
            AssertWithLogAndBreak(pthread_equal(m_uiThreadId, currentThreadId), "Must be running on nominated UI thread", file, line);
        }

        void RemoveNominationForUiThread()
        {
            m_hasSetUiThreadId = false;
        }

        void NominateCurrentlyRunningThreadAsNativeThread()
        {
            if(m_hasSetNativeThreadId){
                Eegeo_TTY("Warning: Native thread has already been set.\n");
            }
            m_nativeThreadId = pthread_self();
            m_hasSetNativeThreadId = true;
        }

        void AssertCurrentlyRunningOnNominatedNativeThread(const char* file, int line)
        {
            Eegeo_ASSERT(m_hasSetNativeThreadId, "Native thread has not yet been nominated.\n");
            const pthread_t currentThreadId(pthread_self());
            AssertWithLogAndBreak(pthread_equal(m_nativeThreadId, currentThreadId), "Must be running on nominated native thread", file, line);
        }

        void RemoveNominationForNativeThread()
        {
            m_hasSetNativeThreadId = false;
        }
    };

    AndroidAppThreadIdentifier g_threadIdentifiers;
}

#define PERFORM_THREAD_VALIDATION_ASSERTIONS

namespace ExampleApp
{
    namespace AndroidAppThreadAssertions
    {
#if defined(PERFORM_THREAD_VALIDATION_ASSERTIONS)
        void NominateCurrentlyRunningThreadAsUiThread()
        {
            g_threadIdentifiers.NominateCurrentlyRunningThreadAsUiThread();
        }

        void AssertCurrentlyRunningOnNominatedUiThread(const char* file, int line)
        {
            g_threadIdentifiers.AssertCurrentlyRunningOnNominatedUiThread(file, line);
        }

        void RemoveNominationForUiThread()
        {
            g_threadIdentifiers.RemoveNominationForUiThread();
        }

        void NominateCurrentlyRunningThreadAsNativeThread()
        {
            g_threadIdentifiers.NominateCurrentlyRunningThreadAsNativeThread();
        }

        void AssertCurrentlyRunningOnNominatedNativeThread(const char* file, int line)
        {
            g_threadIdentifiers.AssertCurrentlyRunningOnNominatedNativeThread(file, line);
        }

        void RemoveNominationForNativeThread()
        {
            g_threadIdentifiers.RemoveNominationForNativeThread();
        }
#else
        void NominateCurrentlyRunningThreadAsUiThread() { }

        void AssertCurrentlyRunningOnNominatedUiThread(const char* file, int line) { }

        void RemoveNominationForUiThread() { }

        void NominateCurrentlyRunningThreadAsNativeThread() { }

        void AssertCurrentlyRunningOnNominatedNativeThread(const char* file, int line) { }

        void RemoveNominationForNativeThread() { }
#endif

    }
}

#undef PERFORM_THREAD_VALIDATION_ASSERTIONS
