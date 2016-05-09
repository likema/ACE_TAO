
//=============================================================================
/**
 *  @file    Strenvdup_Test.cpp
 *
 *  It verifies ACE_OS::strenvdup.
 *
 *
 *  @author Like Ma <likemartinma@gmail.com>
 */
//=============================================================================


#include "test_config.h"
#include "ace/OS_NS_stdlib.h"
#include "ace/OS_NS_string.h"


int run_main (int, ACE_TCHAR *[])
{
  ACE_START_TEST (ACE_TEXT ("Strenvdup_Test"));

  ACE_OS::putenv (ACE_TEXT ("foo=bar"));
  ACE_OS::putenv (ACE_TEXT ("hello=world"));

  ACE_TEST_ASSERT (ACE_OS::strenvdup (0) == 0);

  ACE_TCHAR* p = ACE_OS::strenvdup (ACE_TEXT (""));
  ACE_TEST_ASSERT (p && *p == 0);
  ACE_OS::free (p);

  p = ACE_OS::strenvdup (ACE_TEXT ("$"));
  ACE_TEST_ASSERT (p && ACE_OS::strcmp (p, ACE_TEXT("$")) == 0);
  ACE_OS::free (p);

  p = ACE_OS::strenvdup (ACE_TEXT ("$foo"));
  ACE_TEST_ASSERT (p && ACE_OS::strcmp (p, ACE_TEXT("bar")) == 0);
  ACE_OS::free (p);

  p = ACE_OS::strenvdup (ACE_TEXT ("$foo$"));
  ACE_TEST_ASSERT (p && ACE_OS::strcmp (p, ACE_TEXT("bar$")) == 0);
  ACE_OS::free (p);

  p = ACE_OS::strenvdup (ACE_TEXT ("$foo/app"));
  ACE_TEST_ASSERT (p && ACE_OS::strcmp (p, ACE_TEXT("bar/app")) == 0);
  ACE_OS::free (p);

  p = ACE_OS::strenvdup (ACE_TEXT ("$foo$hello"));
  ACE_TEST_ASSERT (p && ACE_OS::strcmp (p, ACE_TEXT("barworld")) == 0);
  ACE_OS::free (p);

  p = ACE_OS::strenvdup (ACE_TEXT ("$foo/app/$hello"));
  ACE_TEST_ASSERT (p && ACE_OS::strcmp (p, ACE_TEXT("bar/app/world")) == 0);
  ACE_OS::free (p);

  p = ACE_OS::strenvdup (ACE_TEXT ("$$foo"));
  ACE_TEST_ASSERT (p && ACE_OS::strcmp (p, ACE_TEXT("$bar")) == 0);
  ACE_OS::free (p);

  p = ACE_OS::strenvdup (ACE_TEXT ("$$foo"));
  ACE_TEST_ASSERT (p && ACE_OS::strcmp (p, ACE_TEXT("$bar")) == 0);
  ACE_OS::free (p);

  p = ACE_OS::strenvdup (ACE_TEXT ("/app/$foo"));
  ACE_TEST_ASSERT (p && ACE_OS::strcmp (p, ACE_TEXT("/app/bar")) == 0);
  ACE_OS::free (p);

  p = ACE_OS::strenvdup (ACE_TEXT ("/app/$foo/hello"));
  ACE_TEST_ASSERT (p && ACE_OS::strcmp (p, ACE_TEXT("/app/bar/hello")) == 0);
  ACE_OS::free (p);

  ACE_END_TEST;
  return 0;
}

// vim: set ts=2 sw=2 sts=2 et:
