#ifndef JANSSON_EXTRA_H
#define JANSSON_EXTRA_H

#include <jansson.h>
#include <string.h>
#include <stdbool.h>

static inline json_t *
json_array_get_object_with(json_t *_array, const char *_key, const char *_val) {
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

static inline int
json_object_set_string(json_t *_obj, const char *_key, const char *_val) {
    return json_object_set(_obj, _key, json_string(_val));
}

static inline int
json_object_set_integer(json_t *_obj, const char *_key, long _val) {
    return json_object_set(_obj, _key, json_integer(_val));
}

static inline int
json_object_set_boolean(json_t *_obj, const char *_key, bool _val) {
    return json_object_set(_obj, _key, json_boolean(_val));
}

static inline const char *
json_object_get_string(json_t *_obj, const char *_key) {
    return json_string_value(json_object_get(_obj, _key));
}

static inline long long
json_object_get_integer(json_t *_obj, const char *_key) {
    return json_integer_value(json_object_get(_obj, _key));
}

static inline bool
json_object_get_boolean(json_t *_obj, const char *_key) {
    return json_boolean_value(json_object_get(_obj, _key));
}




#endif
