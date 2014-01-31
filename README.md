# Markdown

A simple Elixir Markdown to HTML conversion library.

Implemented entirely as a [NIF][1] binding to the [Hoedown][2] library.

## Usage

```iex
iex> Markdown.to_html "# Hello World"
"<h1>Hello World</h1>\n"
iex> Markdown.to_html "http://elixir-lang.org/", autolink: true
"<p><a href=\"http://elixir-lang.org/\">http://elixir-lang.org/</a></p>\n"
```

[1]: http://www.erlang.org/doc/tutorial/nif.html
[2]: https://github.com/hoedown/hoedown
