#include "../header/rawshader.h"
#include "../header/file.h"

namespace Crimson{
void RawShader::use() const
{
	if(program == 0)
	{
		printf("Shader::use() -> warning! shader not initialized.\n");
	}
	glUseProgram(program);
}

void RawShader::use_none()
{
	glUseProgram(0);
}

RawShader RawShader::load(fs::path location)
{
	std::string raw_source = File::read(location);

	std::string line;
	std::string vertex;
	std::string fragment;
	char type = 0;
	for(unsigned int i = 0; i < raw_source.size(); i++)
	{
		if(raw_source[i] != '\n')
		{
			line += raw_source[i];
			continue;
		}

		if(line.rfind("#vertex", 0) == 0)
		{
			type = 1;
			line.clear();
			continue;
		}
		else if(line.rfind("#fragment", 0) == 0)
		{
			type = 2;
			line.clear();
			continue;
		}

		if(type == 1)
		{
			vertex += line + '\n';
		}
		else if(type == 2)
		{
			fragment += line + '\n';
		}
		
		line.clear();
	}

	vertex = "#version 430 core\n" + load_shader_recursive(vertex, location);
	fragment = "#version 430 core\n" + load_shader_recursive(fragment, location);
	
	return load_from_raw_sources(vertex, fragment);
}

RawShader RawShader::load_from_raw_sources(const std::string& vertex, const std::string& fragment)
{
	unsigned int vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex.c_str());
	unsigned int fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment.c_str());

	RawShader shader;
	shader.program = glCreateProgram();
	glAttachShader(shader.program, vertex_shader);
	glAttachShader(shader.program, fragment_shader);
	glLinkProgram(shader.program);
	
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader;
}

std::string RawShader::load_shader_recursive(const std::string& presource, fs::path location)
{
	std::string folder_path = location.parent_path();

	std::string line;
	std::string new_source;
	for(unsigned int i = 0; i < presource.size(); i++)
	{
		if(presource[i] != '\n')
		{
			line += presource[i];
			continue;
		}

		if(line.rfind("#include ", 0) == 0)
		{
			new_source += load_shader_recursive(File::read(folder_path + line.substr(9)), location.string()) + '\n';
			line.clear();
			continue;
		}

		new_source += line + '\n';
		line.clear();
	}

	return new_source;
}

unsigned int RawShader::compile_shader(unsigned int shader_type, const char* shader_source)
{
	unsigned int shader = glCreateShader(shader_type);
	glShaderSource(shader, 1, &shader_source, NULL);
	glCompileShader(shader);
	
	GLint compiled;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if(!compiled)
	{
		GLint infoLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		if(infoLen > 0)
		{
			char* infoLog = (char*) malloc(infoLen);
			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			printf("Failed to compile shader.\n");
			printf("%s\n", infoLog);
			exit(1);
		}
	}

	return shader;
}

unsigned int RawShader::get_uniform_location(const char* name) const
{
	unsigned int uniform = glGetUniformLocation(program, name);
	// if(uniform == (unsigned int)-1)
	// {
	// 	printf("Uniform \"%s\" does not exist or is unused.\n", name);
	// 	exit(1);
	// }
	
	return uniform;
}

void RawShader::set_uniform(const char* name, int value) const
{
	glUniform1i(get_uniform_location(name), value);
}

void RawShader::set_uniform(const char* name, glm::ivec2 value) const
{
	glUniform2i(get_uniform_location(name), value.x, value.y);
}

void RawShader::set_uniform(const char* name, glm::ivec3 value) const
{
	glUniform3i(get_uniform_location(name), value.x, value.y, value.z);
}

void RawShader::set_uniform(const char* name, glm::ivec4 value) const
{
	glUniform4i(get_uniform_location(name), value.x, value.y, value.z, value.w);
}

void RawShader::set_uniform(const char* name, float value) const
{
	glUniform1f(get_uniform_location(name), value);
}

void RawShader::set_uniform(const char* name, glm::vec2 value) const
{
	glUniform2f(get_uniform_location(name), value.x, value.y);
}

void RawShader::set_uniform(const char* name, glm::vec3 value) const
{
	glUniform3f(get_uniform_location(name), value.x, value.y, value.z);
}

void RawShader::set_uniform(const char* name, glm::vec4 value) const
{
	glUniform4f(get_uniform_location(name), value.x, value.y, value.z, value.w);
}

void RawShader::set_uniform(const char* name, glm::mat4 value) const
{
	glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &value[0][0]);
}

template <typename T> void RawShader::uniform(const char* name, T value) const
{
	set_uniform(name, value);
}

} // namespace Crimson