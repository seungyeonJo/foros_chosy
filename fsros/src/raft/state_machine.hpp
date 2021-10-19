/*
 * Copyright (c) 2021 42dot All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AKIT_FAILSAFE_FSROS_RAFT_STATE_MACHINE_HPP_
#define AKIT_FAILSAFE_FSROS_RAFT_STATE_MACHINE_HPP_

#include <tuple>
#include <variant>

namespace akit {
namespace failsafe {
namespace fsros {

template <typename... States>
class StateMachine {
 public:
  template <typename State>
  void transitionTo() {
    std::visit([](auto state) { state->entry(); }, current_state_);
    current_state_ = &std::get<State>(states_);
    std::visit([](auto state) { state->exit(); }, current_state_);
  }

  template <typename Event>
  void handle(const Event &event) {
    std::visit(
        [this, &event](auto state) { state->handle(event).changeState(*this); },
        current_state_);
  }

  int getCurrentStateIndex() { return current_state_.index(); }

 private:
  std::tuple<States...> states_;
  std::variant<States *...> current_state_{&std::get<0>(states_)};
};

}  // namespace fsros
}  // namespace failsafe
}  // namespace akit

#endif  // AKIT_FAILSAFE_FSROS_RAFT_STATE_MACHINE_HPP_
