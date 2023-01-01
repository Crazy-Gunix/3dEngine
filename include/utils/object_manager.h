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

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <vector>

#include <graphics/object.h>

class ObjectManager {
  public:
    ObjectManager();

    void AddObject(Object object);

    std::vector<Object> get_objects();
  private:
    std::vector<Object> objects_;
};

#endif