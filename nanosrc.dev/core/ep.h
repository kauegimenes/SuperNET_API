/*
    Copyright (c) 2012 Martin Sustrik  All rights reserved.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom
    the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef NN_EP_INCLUDED
#define NN_EP_INCLUDED

#include "../transport.h"

#include "../aio/fsm.h"

#include "../utils/list.h"

/*  Events generated by the nn_ep object. */
#define NN_EP_STOPPED 1

struct nn_ep {
    struct nn_fsm fsm;
    int state;
    struct nn_epbase *epbase;
    struct nn_sock *sock;
    struct nn_ep_options options;
    int eid;
    struct nn_list_item item;
    char addr[NN_SOCKADDR_MAX + 1];
    
    /*  Error state for endpoint */
    int last_errno,bind;
    struct nn_transport *transport;
};

int nn_ep_init(struct nn_ep *self, int src, struct nn_sock *sock, int eid,struct nn_transport *transport, int bind, const char *addr);
void nn_ep_term(struct nn_ep *self);

void nn_ep_start(struct nn_ep *self);
void nn_ep_stop(struct nn_ep *self);

void nn_ep_stopped(struct nn_ep *self);

struct nn_ctx *nn_ep_getctx(struct nn_ep *self);
const char *nn_ep_getaddr(struct nn_ep *self);
void nn_ep_getopt(struct nn_ep *self,int32_t level,int32_t option,void *optval, size_t *optvallen);
int nn_ep_ispeer (struct nn_ep *self,int32_t socktype);
//void nn_ep_set_error(struct nn_ep *self,int32_t errnum);
void nn_ep_set_error(struct nn_ep *self,int32_t errnum,char *fname,int32_t linenum);
void nn_ep_clear_error(struct nn_ep *self);
void nn_ep_stat_increment(struct nn_ep *self,int32_t name,int32_t increment);

#endif
