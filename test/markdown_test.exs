defmodule MarkdownTest do
  use ExUnit.Case

  doctest Markdown

  test :tables do
    markdown = """
    |  J  |  O  |
    | --- | --- |
    |  S  |  É  |
    """

  	html = Markdown.to_html(markdown, tables: true)
    assert html =~ ~r/<table>/
  end

  test :autolink do
  	markdown = "http://devintorr.es/"
  	html = Markdown.to_html(markdown, autolink: true)
  	assert html =~ ~r[<a href="http://devintorr.es/">]
  end

  test :fenced_code do
  	markdown = """
  	```
  	Markdown.to_html(markdown)
  	```
  	"""

  	html = Markdown.to_html(markdown, fenced_code: true)
  	assert html =~ ~r/<code>/
  end
end
