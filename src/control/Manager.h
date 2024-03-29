/*
 * 
 *  Copyright (C) 2010  Mattias Runge
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * 
 */

#ifndef CONTROL_MANAGER_H
#define CONTROL_MANAGER_H

#include <map>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include "broker/Subscriber.h"

#include "timer/Subscriber.h"
#include "common/common.h"

#include "Node.h"
#include "Module.h"
#include "can/Message.h"
#include "common/common.h"

namespace atom {
namespace control {

class Manager : public broker::Subscriber, public timer::Subscriber
{
public:
  typedef boost::shared_ptr<Manager>                                                                            Pointer;
  typedef std::map<Node::Id, Node::Pointer>                                                                     NodeList;
  typedef std::map<Module::FullId, Module::Pointer>                                                             ModuleList;
  typedef boost::signals2::signal<void(Node::Id, bool available)>                                               SignalOnNodeChange;
  typedef boost::signals2::signal<void(std::string full_id, bool available)>                                    SignalOnModuleChange;
  typedef boost::signals2::signal<void(std::string full_id, std::string command, common::StringMap variables)>  SignalOnModuleMessage;
  
  virtual ~Manager();
  
  static Pointer Instance();
  static void Create();
  static void Delete();
  
  void ConnectSlotNode(const SignalOnNodeChange::slot_type& signal_on_node_change_);
  void ConnectSlotModule(const SignalOnModuleChange::slot_type& slot_on_module_change);
  void ConnectSlotModule(const SignalOnModuleMessage::slot_type& slot_on_module_message);
  
  void SendMessage(std::string full_id, std::string command, common::StringMap variables);
  common::StringList GetAvailableModules();
  
  common::StringList GetAvailableNodes();
  bool ProgramNode(Node::Id node_id, bool is_bios, std::string filename);
  bool ProgramNodeHex(Node::Id node_id, bool is_bios, std::string hex_data);
  bool ResetNode(Node::Id node_id);
  Node::Information GetNodeInformation(Node::Id node_id);
    
private:
    static Pointer instance_;
    
    timer::TimerId  timer_id_;
    NodeList        nodes_;
    ModuleList      modules_;
    Node::Id        active_programming_node_id_;
    
    SignalOnNodeChange    signal_on_node_change_;
    SignalOnModuleChange  signal_on_module_change_;
    SignalOnModuleMessage signal_on_module_message_;
    
    Manager();
    
    void SlotOnMessageHandler(broker::Message::Pointer message);
    void SlotOnTimeoutHandler(timer::TimerId timer_id, bool repeat);
    void SlotOnNewState(Node::Id node_id, Node::State current_state, Node::State target_state);
    
    void SendMessageHandler(std::string full_id, std::string command, common::StringMap variables);
    
    Node::Pointer GetNode(Node::Id node_id);
    Module::Pointer GetModule(Module::Id module_id, std::string module_name, std::string class_name);
    void RemoveModules(Node::Id node_id);
    unsigned int GetNumberOfModules(Node::Id node_id);
};

}; // namespace control
}; // namespace atom

#endif // CONTROL_MANAGER_H
