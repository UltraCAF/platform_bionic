/*
 * Copyright (C) 2012-2014 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _LOGD_LOG_BUFFER_ELEMENT_H__
#define _LOGD_LOG_BUFFER_ELEMENT_H__

#include <sys/types.h>
#include <stdatomic.h>
#include <sysutils/SocketClient.h>
#include <log/log.h>
#include <log/log_read.h>

class LogBufferElement {
    const log_id_t mLogId;
    const uid_t mUid;
    const pid_t mPid;
    const pid_t mTid;
    char *mMsg;
    const unsigned short mMsgLen;
    const uint64_t mSequence;
    const log_time mRealTime;
    static atomic_int_fast64_t sequence;

public:
    LogBufferElement(log_id_t log_id, log_time realtime,
                     uid_t uid, pid_t pid, pid_t tid,
                     const char *msg, unsigned short len);
    virtual ~LogBufferElement();

    log_id_t getLogId() const { return mLogId; }
    uid_t getUid(void) const { return mUid; }
    pid_t getPid(void) const { return mPid; }
    pid_t getTid(void) const { return mTid; }
    unsigned short getMsgLen() const { return mMsgLen; }
    uint64_t getSequence(void) const { return mSequence; }
    static uint64_t getCurrentSequence(void) { return sequence.load(memory_order_relaxed); }
    log_time getRealTime(void) const { return mRealTime; }

    static const uint64_t FLUSH_ERROR;
    uint64_t flushTo(SocketClient *writer);
};

#endif