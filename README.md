# Markdown

A simple Elixir [Markdown][1] to HTML conversion library.

Implemented entirely as a [NIF][2] binding to the [Hoedown][3] library.

## Usage

```iex
iex> Markdown.to_html "# Hello World"
"<h1>Hello World</h1>\n"
iex> Markdown.to_html "http://elixir-lang.org/", autolink: true
"<p><a href=\"http://elixir-lang.org/\">http://elixir-lang.org/</a></p>\n"
```

### Options

* `:tables` - Enables Markdown Extra style tables (default: `false`)
* `:fenced_code` - Enables fenced code blocks (default: `false`)
* `:autolink` - Automatically turn URLs into links (default: `false`)

## TODO

* Use dirty schedulers [when available][4]
* Add more options to the NIF that are [available in Hoedown][5]
* ANSI renderer

[1]: http://daringfireball.net/projects/markdown/
[2]: http://www.erlang.org/doc/tutorial/nif.html
[3]: https://github.com/hoedown/hoedown
[4]: https://github.com/zambal/markdown/commit/792a414de074d96ac47b5b52d212b7197ce04462
[5]: https://github.com/hoedown/hoedown/blob/8ab482af918f6b5c296dca80f0c67e924c06b5c2/bin/hoedown.c#L49
