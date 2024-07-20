#pragma once
//
//  common.hpp
//  ExampleTest
//
//  Created by 김성욱 on 7/20/24.
//

#include <memory>
#include <optional>

class Node;
typedef std::weak_ptr<Node> NodeWeakPtr;

class Stream;
typedef std::optional<std::shared_ptr<Stream>> OptionalStream;

