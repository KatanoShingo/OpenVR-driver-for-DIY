#include "cserverdriver_sample.h"

using namespace vr;

EVRInitError CServerDriver_Sample::Init(vr::IVRDriverContext *pDriverContext)
{
    VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);
    //InitDriverLog( vr::VRDriverLog() );
	for (int i = 0; i < m_pControllers; i++)
	{
		m_pController[i] = new CSampleControllerDriver();
		m_pController[i]->SetControllerIndex(i);
		vr::VRServerDriverHost()->TrackedDeviceAdded(m_pController[i]->GetSerialNumber().c_str(), vr::TrackedDeviceClass_GenericTracker, m_pController[i]);
	}
    return VRInitError_None;
}

void CServerDriver_Sample::Cleanup()
{
    //CleanupDriverLog();
	for (int i = 0; i < m_pControllers; i++)
	{
		delete m_pController[i];
		m_pController[i] = NULL;
	}
}

void CServerDriver_Sample::RunFrame()
{
	for (int i = 0; i < m_pControllers; i++)
	{
		if (m_pController[i]) {
			m_pController[i]->RunFrame();
		}
	}
#if 0
    vr::VREvent_t vrEvent;
    while ( vr::VRServerDriverHost()->PollNextEvent( &vrEvent, sizeof( vrEvent ) ) )
    {
        if ( m_pController )
        {
            m_pController->ProcessEvent(vrEvent);
        }
        if ( m_pController2)
        {
            m_pController2->ProcessEvent(vrEvent);
        }
    }
#endif
}
