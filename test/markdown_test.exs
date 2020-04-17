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

  test :strikethrough do
    markdown = "~~strike~~"
    html = Markdown.to_html(markdown, strikethrough: true)
    assert html == "<p><del>strike</del></p>\n"
  end

  test :underline do
    markdown = "_underline_"
    html = Markdown.to_html(markdown, underline: true)
    assert html == "<p><u>underline</u></p>\n"
  end

  test :highlight do
    markdown = "==highlight=="
    html = Markdown.to_html(markdown, highlight: true)
    assert html == "<p><mark>highlight</mark></p>\n"
  end

  test :quote do
    markdown = "\"quotes\""
    html = Markdown.to_html(markdown, quote: true)
    assert html == "<p><q>quotes</q></p>\n"
  end

  test :superscript do
    markdown = "super^script"
    html = Markdown.to_html(markdown, superscript: true)
    assert html == "<p>super<sup>script</sup></p>\n"
  end

  test :math do
    markdown = "Euler's formula is remarkable: $$e^{i\\pi} + 1 = 0$$"
    html = Markdown.to_html(markdown, math: true)
    assert html == "<p>Euler&#39;s formula is remarkable: \\(e^{i\\pi} + 1 = 0\\)</p>\n"
  end

  test :no_intra_emphasis do
    markdown = "Disable emphasis_between_words"
    html = Markdown.to_html(markdown, no_intra_emphasis: true)
    assert html == "<p>Disable emphasis_between_words</p>\n"
  end

  test :space_headers do
    markdown = """
    #Not a headline
    """

    html = Markdown.to_html(markdown, space_headers: true)
    assert html == "<p>#Not a headline</p>\n"
  end

  test :math_explicit do
    markdown = """
    Euler's formula is remarkable: $$e^{i\\pi} + 1 = 0$$
    """

    html = Markdown.to_html(markdown, math: true, math_explicit: true)
    assert html == "<p>Euler&#39;s formula is remarkable: \\[e^{i\\pi} + 1 = 0\\]</p>\n"
  end

  test :disable_indented_code do
    markdown = """
        msg = "Not rendered as code block"
    """

    html = Markdown.to_html(markdown, disable_indented_code: true)
    assert html == "<p>msg = &quot;Not rendered as code block&quot;</p>\n"
  end

  test :skip_html do
    markdown = "Some <b>html</b>"

    html = Markdown.to_html(markdown, skip_html: true)
    assert html == "<p>Some html</p>\n"
  end

  test :escape_html do
    markdown = "Some <b>html</b>"

    html = Markdown.to_html(markdown, escape: true)
    assert html == "<p>Some &lt;b&gt;html&lt;/b&gt;</p>\n"
  end

  test :hard_wraps do
    markdown = """
    Hard wraps
    between lines
    """

    html = Markdown.to_html(markdown, hard_wrap: true)
    assert html == "<p>Hard wraps<br>\nbetween lines</p>\n"
  end

  test :use_xhtml do
    markdown = """
    Emit tags

    ---

    compatible with XHTML
    """

    html = Markdown.to_html(markdown, use_xhtml: true)
    assert html == "<p>Emit tags</p>\n\n<hr/>\n\n<p>compatible with XHTML</p>\n"
  end
end
