defmodule Mix.Tasks.Compile.Hoedown do
  @shortdoc "Compiles Hoedown"

  def run(_) do
    if match? {:win32, _}, :os.type do
      Mix.shell.info System.cmd("nmake /F Makefile.win priv\\markdown.dll")
    else
      Mix.shell.info System.cmd("make priv/markdown.so")
    end
  end
end

defmodule Markdown.Mixfile do
  use Mix.Project

  @version String.strip(File.read!("VERSION"))

  def project do
    [ app: :markdown,
      version: @version,
      elixir: "~> 0.14.0",
      compilers: [:hoedown, :elixir, :app],
      deps: deps ]
  end

  # Configuration for the OTP application
  def application do
    []
  end

  # Returns the list of dependencies in the format:
  # { :foobar, "~> 0.1", git: "https://github.com/elixir-lang/foobar.git" }
  defp deps do
    [ { :hoedown, github: "hoedown/hoedown", app: false } ]
  end
end
