// Copyright 2022 Jacob Gibson

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <graphics/model.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb_image.h>

Model::Model(bool gamma) : gamma_correction_(gamma) {}

void Model::Draw(Shader& shader) {
  for (unsigned int i = 0; i < meshes_.size(); i++)
    meshes_[i].Draw(shader);
}

void Model::LoadModel(std::string const& kPath) {
  std::cout << "Loading model \"" << kPath << "\".\n";

  // read file via ASSIMP
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(kPath, aiProcess_Triangulate |
                                           aiProcess_GenSmoothNormals |
                                           aiProcess_FlipUVs |
                                           aiProcess_CalcTangentSpace);
  // check for errors
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || 
      !scene->mRootNode) { // if is Not Zero
    std::cerr << "ERROR::ASSIMP:: " << importer.GetErrorString() << '\n';
    return;
  }
  // retrieve the directory path of the filepath
  directory_ = kPath.substr(0, kPath.find_last_of('/'));

  // process ASSIMP's root node recursively
  ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* pNode, const aiScene* pScene) {
  // process each mesh located at the current node
  for (unsigned int i = 0; i < pNode->mNumMeshes; i++) {
    // the node object only contains indices to index the actual objects in the scene. 
    // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
    aiMesh* pMesh = pScene->mMeshes[pNode->mMeshes[i]];
    meshes_.push_back(ProcessMesh(pMesh, pScene));
  }
  // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
  for (unsigned int i = 0; i < pNode->mNumChildren; i++)
    ProcessNode(pNode->mChildren[i], pScene);
}

Mesh Model::ProcessMesh(aiMesh* pMesh, const aiScene *pScene) {
  // data to fill
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  // walk through each of the mesh's vertices
  for (unsigned int i = 0; i < pMesh->mNumVertices; i++) {
    Vertex vertex;
    glm::vec3 vector; // we declare a placeholder std::vector since assimp uses its own std::vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
    // positions
    vector.x = pMesh->mVertices[i].x;
    vector.y = pMesh->mVertices[i].y;
    vector.z = pMesh->mVertices[i].z;
    vertex.position = vector;
    // normals
    if (pMesh->HasNormals()) {
      vector.x = pMesh->mNormals[i].x;
      vector.y = pMesh->mNormals[i].y;
      vector.z = pMesh->mNormals[i].z;
      vertex.normal = vector;
    }
    // texture coordinates
    if (pMesh->mTextureCoords[0]) { // does the mesh contain texture coordinates?
      glm::vec2 vec;
      // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
      // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
      vec.x = pMesh->mTextureCoords[0][i].x; 
      vec.y = pMesh->mTextureCoords[0][i].y;
      vertex.tex_coords = vec;
      // tangent
      vector.x = pMesh->mTangents[i].x;
      vector.y = pMesh->mTangents[i].y;
      vector.z = pMesh->mTangents[i].z;
      vertex.tangent = vector;
      // bitangent
      vector.x = pMesh->mBitangents[i].x;
      vector.y = pMesh->mBitangents[i].y;
      vector.z = pMesh->mBitangents[i].z;
      vertex.bitangent = vector;
    } else vertex.tex_coords = glm::vec2(0.0f, 0.0f);

    vertices.push_back(vertex);
  }
  // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
  for (unsigned int i = 0; i < pMesh->mNumFaces; i++) {
    aiFace face = pMesh->mFaces[i];
    // retrieve all indices of the face and store them in the indices std::vector
    for (unsigned int j = 0; j < face.mNumIndices; j++)
      indices.push_back(face.mIndices[j]);
  }
  // process materials
  aiMaterial* pMaterial = pScene->mMaterials[pMesh->mMaterialIndex];
  // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
  // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
  // Same applies to other texture as the following list summarizes:
  // diffuse: texture_diffuseN
  // specular: texture_specularN
  // normal: texture_normalN

  // 1. diffuse maps
  std::vector<Texture> diffuseMaps = LoadMaterialTextures(pMaterial,
                                                         aiTextureType_DIFFUSE,
                                                         "texture_diffuse");
  textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
  // 2. specular maps
  std::vector<Texture> specularMaps = LoadMaterialTextures(pMaterial,
                                                        aiTextureType_SPECULAR,
                                                        "texture_specular");
  textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
  // 3. normal maps
  std::vector<Texture> normalMaps = LoadMaterialTextures(pMaterial,
                                                         aiTextureType_HEIGHT,
                                                         "texture_normal");
  textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
  // 4. height maps
  std::vector<Texture> heightMaps = LoadMaterialTextures(pMaterial,
                                                        aiTextureType_AMBIENT,
                                                        "texture_height");
  textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

  // return a mesh object created from the extracted mesh data
  return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* pMat,
                                                 aiTextureType type,
                                                 std::string typeName) {
  std::vector<Texture> textures;
  for (unsigned int i = 0; i < pMat->GetTextureCount(type); i++) {
    aiString str;
    pMat->GetTexture(type, i, &str);
    // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
    bool skip = false;
    for (unsigned int j = 0; j < textures_loaded_.size(); j++) {
      if (std::strcmp(textures_loaded_[j].path.data(), str.C_Str()) == 0) {
        textures.push_back(textures_loaded_[j]);
        skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
        break;
      }
    }
    if (!skip) {  // if texture hasn't been loaded already, load it
      Texture texture;
      texture.id = TextureFromFile(str.C_Str(), directory_);
      texture.type = typeName;
      texture.path = str.C_Str();
      textures.push_back(texture);
      textures_loaded_.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
    }
  }
  return textures;
}

unsigned int TextureFromFile(const char* kPath, const std::string& kDirectory,
                             bool gamma) {
  std::string filename = std::string(kPath);
  filename = kDirectory + '/' + filename;

  unsigned int textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  std::cout << "Loading image \"" << filename << "\".\n";
  unsigned char *pData = stbi_load(filename.c_str(), &width, &height,
                                   &nrComponents, 0);
  if (pData) {
    GLenum format;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, pData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(pData);
  } else {
    std::cerr << "Texture failed to load at path: " << kPath << '\n';
    stbi_image_free(pData);
  }

  return textureID;
}