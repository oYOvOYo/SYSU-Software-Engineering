function [ output_img ] = Gaussian_Noise( input_img, means, variance)
  
  pd = makedist('Normal','mu', means,'sigma', sqrt(variance));
  
  noise = (random(pd, size(input_img)))./255;
  output_img = input_img + noise;

end

