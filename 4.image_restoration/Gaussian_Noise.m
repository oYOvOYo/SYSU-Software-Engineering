function [ output_img ] = Gaussian_Noise( input_img, means, variance)
  
  [m, n] = size(input_img);
  variance = variance / (m * n);
  pd = makedist('Normal','mu', means,'sigma', sqrt(variance));
  
  noise = (random(pd, size(input_img)));
  output_img = input_img + noise;

end

