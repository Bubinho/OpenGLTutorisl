#version 330 core
precision highp float;
uniform vec3 metas [10];
uniform float my;
uniform sampler1D ourTexture;

out vec4 FragColor;

//in vec3 ourColor;

void main()
{
//----------normal balls ---------------
	/*float x =  gl_FragCoord.x;
	float y  = gl_FragCoord.y;
	vec4 mb;
	
	for(int i = 0; i < 10; i++)
	{
		
		//vec3 mb = metas[i];
		 mb = texture(ourTexture, i/10.f);
		float dx = mb.x - x;
        float dy = mb.y - y;
        float r = mb.z;
		
        if (dx*dx + dy*dy < r*r)
		{
			// we are in a particle
			FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
			return;
		}
	}

    FragColor = vec4(mb.x, 0.0f, 0.0f, 1.0f);*/

	//-------------------- metaballs --------------------------
	float x =  gl_FragCoord.x;
	float y  = gl_FragCoord.y;
	float v = 0.0f;

	for(int i = 0; i < 10; i++)
	{
		vec3 mb = metas[i];
		float dx = mb.x - x;
        float dy = mb.y - y;
        float r = mb.z;
		v += r*r / (dx*dx+dy*dy); 
	}
	if( v > 1.0)
	{
		FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	}else{
		FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	}

}