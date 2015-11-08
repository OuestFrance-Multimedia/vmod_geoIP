#define HOSTNAME_MAX_SIZE 200
#include <stdio.h>
#include <stdlib.h>

#include "vrt.h"
#include "vrt_obj.h"
#include "cache/cache.h"

#include "vcc_if.h"

#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <GeoIP.h>

static GeoIP *gi = NULL;
static GeoIP *giV6 = NULL;

int
init_function(struct vmod_priv *priv, const struct VCL_conf *conf)
{
	return (0);
}

VCL_VOID
vmod_get_country_code(const struct vrt_ctx *ctx)
{
  vmod_get_country_code_IP(ctx, VRT_r_client_ip(ctx));
}

VCL_VOID
vmod_get_country_code_IP(const struct vrt_ctx *ctx, VCL_IP client_ip)
{
  const char* country = NULL;

  if (gi == NULL)
    gi = GeoIP_open_type(GEOIP_COUNTRY_EDITION , GEOIP_STANDARD);

  if (giV6 == NULL)
    giV6 = GeoIP_open_type(GEOIP_COUNTRY_EDITION_V6 , GEOIP_STANDARD);

  const char* ip=VRT_IP_string(ctx, client_ip);
  //const char* ip="6.6.6.6";

  if (ip != NULL) {
    if (strstr(ip, ":") != NULL) {
      country = GeoIP_country_code_by_addr_v6(giV6, ip);
    }
    else {
      country = GeoIP_country_code_by_addr(gi, ip);
    }
  }


  country = country ? country : "Unknown";

  static const struct gethdr_s VGC_HDR_REQ_VARNISH_X_COUNTRY_CODE = { HDR_REQ, "\017X-Country-Code:"};
  VRT_SetHdr(ctx, &VGC_HDR_REQ_VARNISH_X_COUNTRY_CODE, country, vrt_magic_string_end);
}
