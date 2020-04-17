defmodule Markdown do
  @moduledoc """
  Markdown to HTML conversion.
  """

  @on_load { :init, 0 }

  app = Mix.Project.config[:app]

  def init do
    path = :filename.join(:code.priv_dir(unquote(app)), 'markdown')
    :ok = :erlang.load_nif(path, 0)
  end

  @doc ~S"""
  Converts a Markdown document to HTML:

      iex> Markdown.to_html "# Hello World"
      "<h1>Hello World</h1>\n"
      iex> Markdown.to_html "http://elixir-lang.org/", autolink: true
      "<p><a href=\"http://elixir-lang.org/\">http://elixir-lang.org/</a></p>\n"

  Available output options:

  * `:tables` - Enables Markdown Extra style tables (default: `false`)
  * `:fenced_code` - Enables fenced code blocks (default: `false`)
  * `:autolink` - Automatically turn URLs into links (default: `false`)
  * `:strikethrough` - Parse ~~stikethrough~~ spans (default: `false`)
  * `:underline` - Parse _underline_ instead of emphasis (default: `false`)
  * `:highlight` - Parse ==highlight== spans (default: `false`)
  * `:quote` - Render \"quotes\" as <q>quotes</q> (default: `false`)
  * `:superscript` - Parse super^script (default: `false`)
  * `:math` - Parse TeX $$math$$ syntax, Kramdown style (default: `false`)
  * `:no_intra_emphasis` - Disable emphasis_between_words (default: `false`)
  * `:space_headers` - Require a space after '#' in headers (default: `false`)
  * `:math_explicit` - Instead of guessing by context, parse $inline math$ and $$always block math$$ (requires `math: true`) (default: `false`)
  * `:disable_indented_code` - Don't parse indented code blocks (default: `false`)
  * `:skip_html` - Strip all HTML tags (default: `false`)
  * `:escape` - Escape all HTML (default: `false`)
  * `:hard_wrap` - Render each linebreak as <br> (default: `false`)
  * `:use_xhtml` - Render XHTML (default: `false`)

  """
  @spec to_html(doc :: String.t) :: String.t
  @spec to_html(doc :: String.t, options :: Keyword.t) :: String.t
  def to_html(doc, options \\ [])

  def to_html(_, _) do
    exit(:nif_library_not_loaded)
  end
end
