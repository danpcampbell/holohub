/*
 * SPDX-FileCopyrightText: Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
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

#pragma once

#include <memory>
#include "adv_network_common.h"
#include "holoscan/holoscan.hpp"

namespace holoscan::ops {
/*
  Class for handling data from a high-speed network. This can be used for low-speed networks too,
  but requires more configuration that's not necessarily needed with low-speed networks.
*/

enum PacketLayerFill {
  FILL_NONE = 0,
  FILL_ETH = 1,
  FILL_IP = 2,
  FILL_UDP = 3
};

class AdvNetworkOpTx : public Operator {
  class AdvNetworkOpTxImpl;

 public:
    HOLOSCAN_OPERATOR_FORWARD_ARGS(AdvNetworkOpTx);

    AdvNetworkOpTx() = default;
    ~AdvNetworkOpTx() = default;
    void initialize() override;
    int Init();
    int FreeBurst(AdvNetBurstParams *burst);

    // Holoscan functions
    void setup(OperatorSpec& spec) override;
    void compute(InputContext&, OutputContext& op_output, ExecutionContext&) override;

 private:
    void SetFillInfo();
    Parameter<AdvNetConfigYaml> cfg_;
    AdvNetworkOpTxImpl *impl;

    PacketLayerFill fill[MAX_INTERFACES][MAX_NUM_TX_QUEUES] = {FILL_NONE};
    uint8_t  raw_eth_dst_[MAX_INTERFACES][MAX_NUM_TX_QUEUES][6];
    uint32_t raw_ip_src_[MAX_INTERFACES][MAX_NUM_TX_QUEUES];
    uint32_t raw_ip_dst_[MAX_INTERFACES][MAX_NUM_TX_QUEUES];
    uint16_t raw_udp_src_port_[MAX_INTERFACES][MAX_NUM_TX_QUEUES];
    uint16_t raw_udp_dst_port_[MAX_INTERFACES][MAX_NUM_TX_QUEUES];
};
};  // namespace holoscan::ops
