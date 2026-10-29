#ifndef ARGO_H
#define ARGO_H

#include <stdio.h>
#include <stdlib.h>

/* ---------- JSON Abstract Syntax Tree ---------- */

typedef struct json json;
typedef struct pair pair;

struct pair {
	char	*key;
	json	value;
};

struct json {
	enum {
		MAP,
		INTEGER,
		STRING
	} type;
	union {
		struct {
			pair	*data;
			size_t	size;
		} map;
		int		integer;
		char	*string;
	};
};

/* ---------- Function Prototypes ---------- */

/**
 * Parse a JSON-like structure (maps, strings, integers) from a stream.
 *
 * @param dst    Pointer to the JSON AST to fill.
 * @param stream File stream to read from.
 * @return 1 on success, -1 on failure (prints an error message).
 */
int	argo(json *dst, FILE *stream);

/* Utility functions implemented in main.c or elsewhere */
void	free_json(json j);
void	serialize(json j);

#endif /* ARGO_H */
