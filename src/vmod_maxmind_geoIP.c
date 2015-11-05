#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "vrt.h"
#include "cache/cache.h"

#include "vcc_if.h"

int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf)
{
	return (0);
}

VCL_VOID
vmod_set_x_request_start(const struct vrt_ctx *ctx)
{
  struct timeval detail_time;
  gettimeofday(&detail_time,NULL);
  char start[20];
  sprintf(start, "t=%lu%06lu", detail_time.tv_sec, detail_time.tv_usec);
  static const struct gethdr_s VGC_HDR_REQ_VARNISH_X_REQ_START = { HDR_REQ, "\020X-Request-Start:"};
  VRT_SetHdr(ctx, &VGC_HDR_REQ_VARNISH_X_REQ_START, start, vrt_magic_string_end);
}
