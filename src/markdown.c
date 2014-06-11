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
      }
    }
  }

  ob = hoedown_buffer_new(OUTPUT_UNIT);
  renderer = hoedown_html_renderer_new(0, 0);
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
