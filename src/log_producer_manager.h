//
// Created by ZhangCheng on 20/11/2017.
//

#ifndef LOG_C_SDK_LOG_PRODUCER_MANAGER_H
#define LOG_C_SDK_LOG_PRODUCER_MANAGER_H

#include "log_define.h"
LOG_CPP_START

#include "log_producer_config.h"
#include "log_producer_sender.h"
#include "log_builder.h"
#include "log_queue.h"
#include "log_multi_thread.h"

typedef struct _log_producer_manager
{
    log_producer_config * producer_config;
    volatile uint32_t shutdown;
    volatile uint32_t networkRecover;
    volatile uint32_t totalBufferSize;
    log_queue * loggroup_queue;
    THREAD flush_thread;
    CRITICALSECTION lock;
    COND triger_cond;
    log_group_builder * builder;
    int32_t firstLogTime;
    char * source;
    char * pack_prefix;
    volatile uint32_t pack_index;
    on_log_producer_send_done_function send_done_function;
    log_producer_send_param ** send_param_queue;
    uint64_t send_param_queue_size;
    uint64_t send_param_queue_read;
    uint64_t send_param_queue_write;
}log_producer_manager;

extern log_producer_manager * create_log_producer_manager(log_producer_config * producer_config);
extern void destroy_log_producer_manager(log_producer_manager * manager);

extern log_producer_result log_producer_manager_add_log(log_producer_manager * producer_manager, int32_t pair_count, char ** keys, size_t * key_lens, char ** values, size_t * val_lens);

LOG_CPP_END

#endif //LOG_C_SDK_LOG_PRODUCER_MANAGER_H
