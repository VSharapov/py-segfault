#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <python2.7/Python.h>

int ullongLen(unsigned long long);

int ullongLen(unsigned long long n){
	if (n < 10){return 1;}
	return 1 + ullongLen(n / 10);
}

char* verboseChar(char c){
	char buf[7] = "[    ]";
	const char *sp[33] = {
		"[NUL ] null",
		"[SOH ] start of heading",
		"[STX ] start of text",
		"[ETX ] end of text",
		"[EOT ] end of transmission",
		"[ENQ ] enquiry",
		"[ACK ] acknowledge",
		"[BEL ] bell",
		"[BS  ] backspace",
		"[HT  ] horizontal tab",
		"[NL  ] new line (or LF, line feed)",
		"[VT  ] vertical tab",
		"[NP  ] new page (or FF, form feed)",
		"[CR  ] carriage return",
		"[SO  ] shift out",
		"[SI  ] shift in",
		"[DLE ] data link escape",
		"[DC1 ] device control 1",
		"[DC2 ] device control 2",
		"[DC3 ] device control 3",
		"[DC4 ] device control 4",
		"[NAK ] negative acknowledge",
		"[SYN ] synchronous idle",
		"[ETB ] end of transmission block",
		"[CAN ] cancel",
		"[EM  ] end of medium",
		"[SUB ] substitute",
		"[ESC ] escape",
		"[FS  ] file separator",
		"[GS  ] group separator",
		"[RS  ] record separator",
		"[US  ] unit separator",
		"[SP  ] space "
	};
	if ((unsigned int)c <= 32){return sp[(unsigned int)c];}
	if ((unsigned int)c == 127){return "[DEL ]";}
	if ((unsigned int)c < 127){buf[2] = c; return buf;}
	snprintf(buf, sizeof(buf), "%s%x%s", "[0x", c & 0xff, "]");
	return buf;
}

static PyObject *py_segfault(PyObject *self, PyObject *args){
	const char *startString;
	char c[2];

	char pyTypeString[] = "s";
	char pyTypeInt[]    = "i";
	char pyTypeUllong[] = "K";

	unsigned long long i;
	int ullong_max_strlen = floor(log10(ULLONG_MAX)) + 1;

	char fmt[20];
	sprintf(fmt, "%%0%dllu: %%s\n", ullongLen(ULLONG_MAX));

	if (!PyArg_ParseTuple(args, pyTypeString, &startString)){
		return NULL;
	}

	for (i = 0; i <= ULLONG_MAX; i++){
		if (startString[0]){
			printf(fmt, i, verboseChar(startString[i]));
		} else {
			snprintf(c, sizeof(c), "%c", startString[i]);
		}
	}

	printf("By some miracle this thing did not segfault.\n");

	return Py_BuildValue(pyTypeUllong, 0);
}

static PyMethodDef segfaultModule_methods[] = {
	{"segfault", py_segfault, METH_VARARGS,
	 "Segfault by reading a string past the null byte."},
	{NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initsegfault(void){
(void) Py_InitModule("segfault", segfaultModule_methods);
}

