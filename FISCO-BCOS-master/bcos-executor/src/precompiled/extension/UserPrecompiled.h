/**
 *  Copyright (C) 2021 FISCO BCOS.
 *  SPDX-License-Identifier: Apache-2.0
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * @file UserPrecompiled.h
 * @author: kyonRay
 * @date 2021-05-30
 */
#pragma once
#include "CpuHeavyPrecompiled.h"
#include "DagTransferPrecompiled.h"
#include "HelloWorldPrecompiled.h"
#include "PermissionPrecompiledInterface.h"
#include "SmallBankPrecompiled.h"

namespace bcos::precompiled
{
static const constexpr std::string_view DEFAULT_PERMISSION_ADDRESS =
    "0000000000000000000000000000000000001005";
}  // namespace bcos::precompiled
