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

#include "akit/failover/foros/data.hpp"

#include <vector>

namespace akit {
namespace failover {
namespace foros {

Data::Data() {}

Data::Data(uint64_t index, std::vector<uint8_t> data, uint64_t term)
    : index_(index), data_(data), term_(term) {}

}  // namespace foros
}  // namespace failover
}  // namespace akit
