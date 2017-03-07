defmodule Mix.Tasks.Compile.Hoedown do
  def run(_) do
    if match? {:win32, _}, :os.type do
      {result, _error_code} = System.cmd("nmake", ["/F", "Makefile.win", "priv\\markdown.dll"], stderr_to_stdout: true)
      IO.binwrite result
    else
      {result, _error_code} = System.cmd("make", ["priv/markdown.so"], stderr_to_stdout: true)
      IO.binwrite result
    end
    :ok
  end
end

defmodule Markdown.Mixfile do
  use Mix.Project

  @version "0.1.0"

  def project do
    [app: :markdown,
     version: @version,
     elixir: ">= 0.14.3 and < 2.0.0",
     compilers: [:hoedown, :elixir, :app],
     deps: deps()]
  end

  def application do
    []
  end

  defp deps do
    [{:hoedown, github: "hoedown/hoedown", app: false}]
  end
end
