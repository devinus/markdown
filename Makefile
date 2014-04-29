MIX = mix
CFLAGS = -g -O3 -ansi -pedantic -Wall -Wextra -Wno-unused-parameter

ERLANG_PATH = $(shell erl -eval 'io:format("~s", [lists:concat([code:root_dir(), "/erts-", erlang:system_info(version), "/include"])])' -s init stop -noshell)
CFLAGS += -I$(ERLANG_PATH)

ifeq ($(wildcard deps/hoedown),)
	HOEDOWN_PATH = ../hoedown
else
	HOEDOWN_PATH = deps/hoedown
endif

CFLAGS += -I$(HOEDOWN_PATH)/src

ifneq ($(OS),Windows_NT)
	CFLAGS += -fPIC

	ifeq ($(shell uname),Darwin)
		LDFLAGS += -dynamiclib -undefined dynamic_lookup
	endif
endif

.PHONY: all markdown clean

all: markdown

markdown:
	$(MIX) compile

priv/markdown.so: src/markdown.c
	$(MAKE) -C $(HOEDOWN_PATH) libhoedown.a
	$(CC) $(CFLAGS) -shared $(LDFLAGS) -L$(HOEDOWN_PATH) -lhoedown -o $@ src/markdown.c

clean:
	$(MIX) clean
	$(MAKE) -C $(HOEDOWN_PATH) clean
	$(RM) $(HOEDOWN_PATH)/libhoedown.a
	$(RM) priv/markdown.so
