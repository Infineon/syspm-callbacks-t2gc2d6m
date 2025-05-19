/*******************************************************************************
* \file mtb_syspm_callbacks_nvm_flashc.h
*
* Description:
* Provides the implementation for syspm callbacks for the FLASHC IP.
*
********************************************************************************
* \copyright
* Copyright 2024-2024 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/
#pragma once

#include "cy_pdl.h"
#include "cy_utils.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if defined (CY_IP_MXFLASHC_VERSION_ECT) || defined (CY_IP_MXS40FLASHC)

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 8.13', 3, \
                             'API definitions must match between IPs and not all IPs allow the arguments to be const');
//--------------------------------------------------------------------------------------------------
// _mtb_syspm_nvm_check_ready
//--------------------------------------------------------------------------------------------------
__STATIC_INLINE bool _mtb_syspm_nvm_check_ready(mtb_syspm_nvm_type_t type, void* base)
{
    bool allow = true;
    CY_UNUSED_PARAMETER(base);
    /* A note on the "(uint32_t)enum == (uint32_t)enum" below - in some very specific
     * cases, the basic "enum == enum" can be automatically cast into a
     * "int32_t == uint32_t" comparison.  Cast both to uint32_t to avoid this. */
    if ((uint32_t)(type) == (uint32_t)(MTB_SYSPM_NVM_TYPE_FLASH))
    {
        if (CY_RSLT_SUCCESS != Cy_Flash_IsOperationComplete())
        {
            #if defined (CY_IP_MXFLASHC_VERSION_ECT)
            /* The SROM API response is invalid unless a flash operation has occurred at
                least once. Therefore allow that case as an exception. */
            un_srom_api_resps_t resp = {{ 0UL }};
            cy_en_srom_api_status_t status = Cy_Srom_GetApiResponse(&resp);
            if (CY_SROM_STATUS_INVALID != status)
            #endif
            {
                allow = false;
            }
        }
    }
    return allow;
}


//--------------------------------------------------------------------------------------------------
// _mtb_syspm_nvm_before_transition
//--------------------------------------------------------------------------------------------------
__STATIC_INLINE bool _mtb_syspm_nvm_before_transition(mtb_syspm_nvm_type_t type, void* base)
{
    /* This IP needs no before-transition update */
    CY_UNUSED_PARAMETER(type);
    CY_UNUSED_PARAMETER(base);
    return true;
}


//--------------------------------------------------------------------------------------------------
// _mtb_syspm_nvm_after_transition
//--------------------------------------------------------------------------------------------------
__STATIC_INLINE bool _mtb_syspm_nvm_after_transition(mtb_syspm_nvm_type_t type, void* base)
{
    /* This IP needs no after-transition update */
    CY_UNUSED_PARAMETER(type);
    CY_UNUSED_PARAMETER(base);
    return true;
}


//--------------------------------------------------------------------------------------------------
// _mtb_syspm_nvm_check_fail
//--------------------------------------------------------------------------------------------------
__STATIC_INLINE bool _mtb_syspm_nvm_check_fail(mtb_syspm_nvm_type_t type, void* base)
{
    /* This IP needs no check-fail update */
    CY_UNUSED_PARAMETER(type);
    CY_UNUSED_PARAMETER(base);
    return true;
}


CY_MISRA_BLOCK_END('MISRA C-2012 Rule 8.13');

#endif /* defined (CY_IP_MXFLASHC_VERSION_ECT) || defined (CY_IP_MXS40FLASHC) */

#if defined(__cplusplus)
}
#endif
