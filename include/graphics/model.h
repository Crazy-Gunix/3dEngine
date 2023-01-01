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

#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <graphics/mesh.h>
#include <graphics/shader.h>

unsigned int TextureFromFile(const char* kPath, const std::string& kDirectory, 
                            bool gamma = false);

class Model{
  public:
    // model data 
    std::vector<Texture> textures_loaded_;  // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh> meshes_;
    std::string directory_;
    bool gamma_correction_;

    // constructor, expects a filepath to a 3D model.
    Model(bool gamma = false);

    // draws the model, and thus all its meshes
    void Draw(Shader& shader);

    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes std::vector.
    void LoadModel(std::string const& kPath);
  private:
    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void ProcessNode(aiNode* pNode, const aiScene* pScene);

    Mesh ProcessMesh(aiMesh* pMesh, const aiScene* pScene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    std::vector<Texture> LoadMaterialTextures(aiMaterial* pMat, 
                                              aiTextureType type, 
                                              std::string type_name);
};

#endif

