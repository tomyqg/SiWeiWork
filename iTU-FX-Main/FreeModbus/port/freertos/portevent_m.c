/*
 * FreeModbus Libary: RT-Thread Port
 * Copyright (C) 2013 Armink <armink.ztl@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: portevent_m.c v 1.60 2013/08/13 15:07:05 Armink add Master Functions$
 */

/* ----------------------- System includes ----------------------------------*/

/* ----------------------- Platform includes --------------------------------*/
#include "cmsis_os.h"
/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mb_m.h"
#include "mbport.h"
#include "port.h"

#if MB_MASTER_RTU_ENABLED > 0 || MB_MASTER_ASCII_ENABLED > 0
/* ----------------------- Defines ------------------------------------------*/
/* ----------------------- Variables ----------------------------------------*/
//static struct rt_semaphore xMasterRunRes;
static osMessageQId MsgModbus;
static osSemaphoreId SemModbus;
/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBMasterPortEventInit( void )
{
    BOOL            bStatus = FALSE;
    osMessageQDef(MsgModbus, 1, eMBEventType);      
    MsgModbus = osMessageCreate(osMessageQ(MsgModbus),NULL );
    if( NULL != MsgModbus)
    {
        bStatus = TRUE;
    }
    return bStatus;
}

BOOL
xMBMasterPortEventPost( eMBMasterEventType eEvent )
{
    BOOL            bStatus = FALSE;
    if( osOK ==osMessagePut(MsgModbus,( uint32_t )eEvent,portTICK_RATE_MS * 50)) // maybe the timeout should be osWaitForever
    {
        bStatus = TRUE;
    } 
    return bStatus;
}



BOOL
xMBMasterPortEventGet( eMBMasterEventType * eEvent )
{
    BOOL            xEventHappened = FALSE;
    osEvent evt;
    evt = osMessageGet(MsgModbus,portTICK_RATE_MS * 50);
    if(osOK == evt.status)
    {       
        *eEvent = (eMBMasterEventType)evt.value.v; 
        xEventHappened = TRUE;
    }
    return xEventHappened;
}
/**
 * This function is initialize the OS resource for modbus master.
 * Note:The resource is define by OS.If you not use OS this function can be empty.
 *
 */
void vMBMasterOsResInit( void )
{
    osSemaphoreDef(SemModbus);
    SemModbus = osSemaphoreCreate(osSemaphore(SemModbus),1);
//    rt_sem_init(&xMasterRunRes, "master res", 0x01 , RT_IPC_FLAG_PRIO);
//    vSemaphoreCreateBinary(xSemHdl);
}

/**
 * This function is take Mobus Master running resource.
 * Note:The resource is define by Operating System.If you not use OS this function can be just return TRUE.
 *
 * @param lTimeOut the waiting time.
 *
 * @return resource taked result
 */
BOOL xMBMasterRunResTake( uint32_t lTimeOut )
{
    /*If waiting time is -1 .It will wait forever */
//    return rt_sem_take(&xMasterRunRes, lTimeOut) ? FALSE : TRUE ;
    
    return (osOK == osSemaphoreWait(SemModbus,lTimeOut))? TRUE:FALSE;
}

/**
 * This function is release Mobus Master running resource.
 * Note:The resource is define by Operating System.If you not use OS this function can be empty.
 *
 */
void vMBMasterRunResRelease( void )
{
    /* release resource */
//    rt_sem_release(&xMasterRunRes);
    osSemaphoreRelease(SemModbus);
}

/**
 * This is modbus master respond timeout error process callback function.
 * @note There functions will block modbus master poll while execute OS waiting.
 * So,for real-time of system.Do not execute too much waiting process.
 *
 * @param ucDestAddress destination salve address
 * @param pucPDUData PDU buffer data
 * @param ucPDULength PDU buffer length
 *
 */
void vMBMasterErrorCBRespondTimeout(UCHAR ucDestAddress, const UCHAR* pucPDUData,
        USHORT ucPDULength)
{
    /**
     * @note This code is use OS's event mechanism for modbus master protocol stack.
     * If you don't use OS, you can change it.
     */
//    rt_event_send(&xMasterOsEvent, EV_MASTER_ERROR_RESPOND_TIMEOUT);
    xMBMasterPortEventPost(EV_MASTER_ERROR_RESPOND_TIMEOUT);

    /* You can add your code under here. */

}

/**
 * This is modbus master receive data error process callback function.
 * @note There functions will block modbus master poll while execute OS waiting.
 * So,for real-time of system.Do not execute too much waiting process.
 *
 * @param ucDestAddress destination salve address
 * @param pucPDUData PDU buffer data
 * @param ucPDULength PDU buffer length
 *
 */
void vMBMasterErrorCBReceiveData(UCHAR ucDestAddress, const UCHAR* pucPDUData,
        USHORT ucPDULength) 
{
    /**
     * @note This code is use OS's event mechanism for modbus master protocol stack.
     * If you don't use OS, you can change it.
     */
//    rt_event_send(&xMasterOsEvent, EV_MASTER_ERROR_RECEIVE_DATA);
    xMBMasterPortEventPost(EV_MASTER_ERROR_RECEIVE_DATA);
    /* You can add your code under here. */

}

/**
 * This is modbus master execute function error process callback function.
 * @note There functions will block modbus master poll while execute OS waiting.
 * So,for real-time of system.Do not execute too much waiting process.
 *
 * @param ucDestAddress destination salve address
 * @param pucPDUData PDU buffer data
 * @param ucPDULength PDU buffer length
 *
 */
void vMBMasterErrorCBExecuteFunction(UCHAR ucDestAddress, const UCHAR* pucPDUData,
        USHORT ucPDULength) 
{
    /**
     * @note This code is use OS's event mechanism for modbus master protocol stack.
     * If you don't use OS, you can change it.
     */
//    rt_event_send(&xMasterOsEvent, EV_MASTER_ERROR_EXECUTE_FUNCTION);
    xMBMasterPortEventPost(EV_MASTER_ERROR_EXECUTE_FUNCTION);
    /* You can add your code under here. */

}

/**
 * This is modbus master request process success callback function.
 * @note There functions will block modbus master poll while execute OS waiting.
 * So,for real-time of system.Do not execute too much waiting process.
 *
 */
void vMBMasterCBRequestScuuess( void ) 
{
    /**
     * @note This code is use OS's event mechanism for modbus master protocol stack.
     * If you don't use OS, you can change it.
     */
//    rt_event_send(&xMasterOsEvent, EV_MASTER_PROCESS_SUCESS);
    xMBMasterPortEventPost(EV_MASTER_PROCESS_SUCESS);
    /* You can add your code under here. */

}

/**
 * This function is wait for modbus master request finish and return result.
 * Waiting result include request process success, request respond timeout,
 * receive data error and execute function error.You can use the above callback function.
 * @note If you are use OS, you can use OS's event mechanism. Otherwise you have to run
 * much user custom delay for waiting.
 *
 * @return request error code
 */
eMBMasterReqErrCode eMBMasterWaitRequestFinish( void ) 
{
    eMBMasterReqErrCode    eErrStatus = MB_MRE_NO_ERR;

    eMBMasterEventType evt;
    xMBMasterPortEventGet(&evt);
    
    switch (evt)
    {
        case EV_MASTER_PROCESS_SUCESS:
        break;
        case EV_MASTER_ERROR_RESPOND_TIMEOUT:
        {
            eErrStatus = MB_MRE_TIMEDOUT;
            break;
        }
        case EV_MASTER_ERROR_RECEIVE_DATA:
        {
            eErrStatus = MB_MRE_REV_DATA;
            break;
        }
        case EV_MASTER_ERROR_EXECUTE_FUNCTION:
        {
            eErrStatus = MB_MRE_EXE_FUN;
            break;
        }
    }
    return eErrStatus;
}

#endif  /* MB_MASTER_RTU_ENABLED > 0 || MB_MASTER_ASCII_ENABLED > 0 */