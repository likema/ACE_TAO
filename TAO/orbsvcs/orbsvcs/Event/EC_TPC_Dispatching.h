// -*- C++ -*-

/**
 *  @file   EC_TPC_Dispatching.h
 *
 *  $Id$
 *
 *  @author Chris Cleeland <cleeland at ociweb.com>
 *
 */

#ifndef TAO_EC_TPC_DISPATCHING_H
#define TAO_EC_TPC_DISPATCHING_H
#include /**/ "ace/pre.h"

#include "ace/Hash_Map_Manager_T.h"
#include "ace/Null_Mutex.h"

#include "EC_Dispatching.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "EC_TPC_Dispatching_Task.h"

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

class TAO_EC_Event_Channel_Base;

/**
 * @class TAO_EC_TPC_Dispatching
 *
 * @brief Dispatching strategy that isolates deliveries to a consumer from any other.
 *
 * This strategy uses a thread per consumer, and was specifically designed to
 * isolate the effects of an ill-behaved consumer from affecting other consumers.
 */
class TAO_RTEvent_Serv_Export TAO_EC_TPC_Dispatching : public TAO_EC_Dispatching
{
public:
  TAO_EC_TPC_Dispatching (TAO_EC_Queue_Full_Service_Object* so);
  ~TAO_EC_TPC_Dispatching ();

  // = The EC_Dispatching methods.
  virtual void activate (void);
  virtual void shutdown (void);
  virtual void push (TAO_EC_ProxyPushSupplier* proxy,
                     RtecEventComm::PushConsumer_ptr consumer,
                     const RtecEventComm::EventSet& event,
                     TAO_EC_QOS_Info& qos_info
                     ACE_ENV_ARG_DECL);
  virtual void push_nocopy (TAO_EC_ProxyPushSupplier* proxy,
                            RtecEventComm::PushConsumer_ptr consumer,
                            RtecEventComm::EventSet& event,
                            TAO_EC_QOS_Info& qos_info
                            ACE_ENV_ARG_DECL);

  int add_consumer (RtecEventComm::PushConsumer_ptr consumer ACE_ENV_ARG_DECL);
  int remove_consumer (RtecEventComm::PushConsumer_ptr consumer ACE_ENV_ARG_DECL);

private:
  // Use our own thread manager
  ACE_Thread_Manager thread_manager_;

  typedef ACE_Hash_Map_Manager_Ex<RtecEventComm::PushConsumer_ptr,TAO_EC_Dispatching_Task*,ACE_Pointer_Hash<RtecEventComm::PushConsumer_ptr>,ACE_Equal_To<RtecEventComm::PushConsumer_ptr>,ACE_Null_Mutex> MAPTYPE;

  // Tweak the default size of this map by #defining
  //    TAO_EC_TPC_DISPATCHING_DEFAULT_MAP_SIZE
  MAPTYPE consumer_task_map_;

  // Lock for modifying the map.  It's not enough to have a lock only
  // on the map, because we have to hold the map constant while doing
  // multiple distinct map manipulations, such as in remove_consumer().
  ACE_SYNCH_MUTEX lock_;

  // Service object information
  TAO_EC_Queue_Full_Service_Object* queue_full_service_object_;  // @@ who will release?
                                // @@ check to see how the factory gets released...
};

TAO_END_VERSIONED_NAMESPACE_DECL

#include /**/ "ace/post.h"
#endif /* TAO_EC_TPC_DISPATCHING_H */
