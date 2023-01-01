/*
Copyright (C) 2023 Jacob Gibson

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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

