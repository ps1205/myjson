#include "leptjson.h"
#include <assert.h>

#define EXPECT(c,ch) do { assert(*c->json == (ch)); c->json++;} while(0) 

static void lept_parse_whitespace(lept_context* c)
{
    const char* p = c->json;
    while(*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
        p++;
    c->json = p;
}

static int lept_parse_null(lept_context* c, lept_value* v)
{
    EXPECT(c,'n');
    if(c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')
        return LEPT_PARSE_INVALID_VALUE;
    c->json += 3;
    v->type = LEPT_NULL;
    return LEPT_PARSE_OK;
}

int lept_parse_value(lept_context* c, lept_value* v)
{
    switch (*c->json)
    {
        case 'n':  return lept_parse_null(c,v);
        case '\0': return LEPT_PARSE_EXPECT_VALUE;
        default:   return LEPT_PARSE_INVALID_VALUE;
    }
}

lept_type lept_get_type(const lept_value* v)
{
    return v->type;
}