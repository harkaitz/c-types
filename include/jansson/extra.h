#ifndef JANSSON_EXTRA_H
#define JANSSON_EXTRA_H

#include <jansson.h>
#include <string.h>

static inline
json_t *json_array_get_object_with(json_t *_array, const char *_key, const char *_val) {
    json_t     *e;
    const char *s;
    size_t      i;
    if (json_is_array(_array)) {
        json_array_foreach(_array, i, e) {
            if (!json_is_object(e)) continue;
            s = json_string_value(json_object_get(e, _key));
            if (!s || strcmp(s, _val)) continue;
            return e;
        }
    }
    return NULL;
}

#endif
