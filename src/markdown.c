#include <string.h>
#include <stdint.h>

#include "erl_nif.h"

#include "buffer.h"
#include "document.h"
#include "html.h"

#define OUTPUT_UNIT 128

typedef struct {
  ERL_NIF_TERM atom_true;
  ERL_NIF_TERM atom_tables;
  ERL_NIF_TERM atom_autolink;
  ERL_NIF_TERM atom_fenced_code;
  ERL_NIF_TERM atom_strikethrough;
  ERL_NIF_TERM atom_underline;
  ERL_NIF_TERM atom_highlight;
  ERL_NIF_TERM atom_quote;
  ERL_NIF_TERM atom_superscript;
  ERL_NIF_TERM atom_math;
  ERL_NIF_TERM atom_no_intra_emphasis;
  ERL_NIF_TERM atom_space_headers;
  ERL_NIF_TERM atom_math_explicit;
  ERL_NIF_TERM atom_disable_indented_code;
  ERL_NIF_TERM atom_skip_html;
  ERL_NIF_TERM atom_escape;
  ERL_NIF_TERM atom_hard_wrap;
  ERL_NIF_TERM atom_use_xhtml;
} markdown_priv;

static ERL_NIF_TERM
to_html(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  ErlNifBinary input;
  ErlNifBinary output;

  markdown_priv* priv;
  ERL_NIF_TERM options;
  ERL_NIF_TERM term;
  const ERL_NIF_TERM* tuple;
  int tuple_size;
  unsigned int extensions;
  unsigned int html_flags;

  hoedown_buffer* ob;
  hoedown_document* document;
  hoedown_renderer* renderer;

  if (enif_inspect_binary(env, argv[0], &input) == 0) {
    return enif_make_badarg(env);
  }

  if (input.size < 1) {
    return argv[0];
  }

  priv = enif_priv_data(env);
  options = argv[1];
  extensions = 0;
  html_flags = 0;

  while (enif_get_list_cell(env, options, &term, &options) != 0) {
    if (enif_get_tuple(env, term, &tuple_size, &tuple) != 0) {
      if (tuple_size > 1) {
        if (enif_compare(tuple[0], priv->atom_tables) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            extensions |= HOEDOWN_EXT_TABLES;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_autolink) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            extensions |= HOEDOWN_EXT_AUTOLINK;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_fenced_code) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            extensions |= HOEDOWN_EXT_FENCED_CODE;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_strikethrough) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            extensions |= HOEDOWN_EXT_STRIKETHROUGH;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_underline) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            extensions |= HOEDOWN_EXT_UNDERLINE;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_highlight) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            extensions |= HOEDOWN_EXT_HIGHLIGHT;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_quote) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            extensions |= HOEDOWN_EXT_QUOTE;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_superscript) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            extensions |= HOEDOWN_EXT_SUPERSCRIPT;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_math) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            extensions |= HOEDOWN_EXT_MATH;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_no_intra_emphasis) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            extensions |= HOEDOWN_EXT_NO_INTRA_EMPHASIS;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_space_headers) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            extensions |= HOEDOWN_EXT_SPACE_HEADERS;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_math_explicit) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            extensions |= HOEDOWN_EXT_MATH_EXPLICIT;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_disable_indented_code) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            extensions |= HOEDOWN_EXT_DISABLE_INDENTED_CODE;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_skip_html) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            html_flags |= HOEDOWN_HTML_SKIP_HTML;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_escape) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            html_flags |= HOEDOWN_HTML_ESCAPE;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_hard_wrap) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            html_flags |= HOEDOWN_HTML_HARD_WRAP;
            continue;
          }
        }

        if (enif_compare(tuple[0], priv->atom_use_xhtml) == 0) {
          if (enif_compare(tuple[1], priv->atom_true) == 0) {
            html_flags |= HOEDOWN_HTML_USE_XHTML;
            continue;
          }
        }
      }
    }
  }

  ob = hoedown_buffer_new(OUTPUT_UNIT);
  renderer = hoedown_html_renderer_new(html_flags, 0);
  document = hoedown_document_new(renderer, extensions, 16);
  hoedown_document_render(document, ob, (uint8_t*) input.data, input.size);

  enif_release_binary(&input);
  hoedown_html_renderer_free(renderer);
  hoedown_document_free(document);

  enif_alloc_binary(ob->size, &output);
  memcpy(output.data, ob->data, ob->size);
  hoedown_buffer_free(ob);

  return enif_make_binary(env, &output);
}

static ErlNifFunc funcs[] = {
  { "to_html", 2, to_html }
};

static int
load(ErlNifEnv* env, void** priv, ERL_NIF_TERM info) {
  markdown_priv* data = enif_alloc(sizeof(markdown_priv));
  if (data == NULL) {
    return 1;
  }

  data->atom_true = enif_make_atom(env, "true");
  data->atom_tables = enif_make_atom(env, "tables");
  data->atom_autolink = enif_make_atom(env, "autolink");
  data->atom_fenced_code = enif_make_atom(env, "fenced_code");
  data->atom_strikethrough = enif_make_atom(env, "strikethrough");
  data->atom_underline = enif_make_atom(env, "underline");
  data->atom_highlight = enif_make_atom(env, "highlight");
  data->atom_quote = enif_make_atom(env, "quote");
  data->atom_superscript = enif_make_atom(env, "superscript");
  data->atom_math = enif_make_atom(env, "math");
  data->atom_no_intra_emphasis = enif_make_atom(env, "no_intra_emphasis");
  data->atom_space_headers = enif_make_atom(env, "space_headers");
  data->atom_math_explicit = enif_make_atom(env, "math_explicit");
  data->atom_disable_indented_code = enif_make_atom(env, "disable_indented_code");
  data->atom_skip_html = enif_make_atom(env, "skip_html");
  data->atom_escape = enif_make_atom(env, "escape");
  data->atom_hard_wrap = enif_make_atom(env, "hard_wrap");
  data->atom_use_xhtml = enif_make_atom(env, "use_xhtml");

  *priv = (void*) data;
  return 0;
}

static int
reload(ErlNifEnv* env, void** priv, ERL_NIF_TERM info) {
  return 0;
}

static int
upgrade(ErlNifEnv* env, void** priv, void** old_priv, ERL_NIF_TERM info) {
  return load(env, priv, info);
}

static void
unload(ErlNifEnv* env, void* priv) {
  enif_free(priv);
}

ERL_NIF_INIT(Elixir.Markdown, funcs, &load, &reload, &upgrade, &unload)
