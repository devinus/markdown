defmodule Markdown do
  @moduledoc """
  Markdown to HTML conversion.
  """

  @on_load { :init, 0 }

  app = Mix.project[:app]

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

  """
  @spec to_html(doc :: String.t) :: String.t
  @spec to_html(doc :: String.t, options :: Keyword.t) :: String.t
  def to_html(doc, options \\ [])

  def to_html(_, _) do
    exit(:nif_library_not_loaded)
  end
end
