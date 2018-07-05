Gem::Specification.new do |s|
  s.name     = 'jekyll-theme-cards'
  s.version  = '0.2.0'
  s.license  = 'MIT'
  s.summary  = 'A Jekyll Theme Uses Many Cards'
  
  s.author   = 'jskyzero'
  s.email    = 'jskyzero@outlook.com'
  s.homepage = 'https://github.com/jskyzero/jekyll-theme-cards'
  
  s.metadata["plugin_type"] = "theme"
  s.files         = `git ls-files -z`.split("\x0").select do |f|
    f.match(%r{^(assets|_(includes|layouts|posts)/|(LICENSE|README|index|_config)((\.(txt|md|markdown|html|yml)|$)))}i)
  end
  
  s.add_runtime_dependency "jekyll", "~> 3.3"
  s.add_development_dependency "bundler", "~> 1.12"
end