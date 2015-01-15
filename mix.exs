defmodule Mix.Tasks.Compile.Hoedown do
  @shortdoc "Compiles Hoedown"

  def run(_) do
    if match? {:win32, _}, :os.type do
      {result, _error_code} = System.cmd("nmake", ["/F", "Makefile.win", "priv\\markdown.dll"], stderr_to_stdout: true)
      Mix.shell.info result
    else
      {result, _error_code} = System.cmd("make", ["priv/markdown.so"], stderr_to_stdout: true)
      Mix.shell.info result
    end
    
    :ok
  end
end

defmodule Markdown.Mixfile do
  use Mix.Project

  @version String.strip(File.read!("VERSION"))

  def project do
    [app: :markdown,
     version: @version,
     elixir: ">= 0.14.3 and < 2.0.0",
     compilers: [:hoedown, :elixir, :app],
     deps: deps]
  end

  # Configuration for the OTP application
  def application do
    []
  end

  # Returns the list of dependencies in the format:
  # { :foobar, "~> 0.1", git: "https://github.com/elixir-lang/foobar.git" }
  defp deps do
    [{:hoedown, github: "hoedown/hoedown", app: false}]
  end
end
