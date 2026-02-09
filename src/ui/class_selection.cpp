#include "class_selection.hpp"

namespace tog {

    ClassSelection::ClassSelection() {
        using namespace rl;

        //create a resource for each class
        for (const int i : std::views::iota(0, static_cast<int>(ClassStats::ClassName::MAX_CLASS_COUNT))) {
            roles.push_back(memnew(ClassStats));
            roles[i]->set_class_name(i);
        }

    }

    void ClassSelection::_ready() {
    }

    void ClassSelection::_physics_process(double delta) {

    }

}
