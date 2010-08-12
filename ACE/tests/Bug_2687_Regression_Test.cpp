/**
 * @file Bug_2687_Regression_Test.cpp
 *
 * Reproduces the problems reported in bug 2687
 *   http://deuce.doc.wustl.edu/bugzilla/show_bug.cgi?id=2687
 *
 * @author Like Ma <likemartinma@gmail.com>
 */

#include "test_config.h"
#include "ace/Acceptor.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Svc_Handler.h"
#include "ace/Log_Msg.h"

ACE_RCSID(tests,
          Bug_2687_Regression_Test, "$Id$")

#define DEFAULT_PORT 23432

/*!
 * @class Simple_Svc_Handler
 *
 * @brief A simple service handler for the test.
 */
class Simple_Svc_Handler :
  public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
public:
  Simple_Svc_Handler (ACE_Thread_Manager* thr_mgr = 0)
    : ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH> (thr_mgr)
  {
  }
};

int
run_main (int, ACE_TCHAR *[])
{
  ACE_START_TEST (ACE_TEXT ("Bug_2687_Regression_Test"));

  ACE_Strategy_Acceptor<Simple_Svc_Handler, ACE_SOCK_ACCEPTOR> acceptor;
  if (acceptor.open (ACE_INET_Addr (DEFAULT_PORT)) < 0)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ACE_TEXT ("Unable to listen port %u: %m\n"),
                       DEFAULT_PORT),
                       1);

  acceptor.close ();

  ACE_END_TEST;

  return 0;
}
