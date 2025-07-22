<a id="readme-top"></a>

<!-- LANGUAGE SWITCH -->

---

<!-- PROJECT LOGO -->

<br />
<div align="center">

<h3 align="center">rc_decision</h3>

<p align="center">
    This project implements a robotic decision-making system using Behavior Trees (BT) within the ROS ecosystem. It integrates custom nodes for navigation, chassis control, and sensor input handling, enabling autonomous task execution. Key features include interaction with ROS services/actions, real-time behavior tree execution, blackboard-based data sharing, and support for joystick control. Built with BehaviorTree.CPP and leveraging ROS’s navigation stack, it provides modular, testable, and deployable robotic intelligence with logging, visualization, and fault-tolerant capabilities.
    <br />
    <a href="https://github.com/gdut-robocon/rc_decision"><strong>Explore the docs »</strong></a>
    <br />
  </p>

<!-- PROJECT SHIELDS -->

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stars][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![License][license-shield]][license-url]

<p align="center">
    <a href="https://github.com/gdut-robocon/rc_decision">View Demo</a>
    ·
    <a href="https://github.com/gdut-robocon/rc_decision/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
    ·
    <a href="https://github.com/gdut-robocon/rc_decision/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->

## 📖 About The Project

This project implements a robotic decision-making system using Behavior Trees (BT) within the ROS ecosystem. It integrates custom nodes for navigation, chassis control, and sensor input handling, enabling autonomous task execution. Key features include interaction with ROS services/actions, real-time behavior tree execution, blackboard-based data sharing, and support for joystick control. Built with BehaviorTree.CPP and leveraging ROS’s navigation stack, it provides modular, testable, and deployable robotic intelligence with logging, visualization, and fault-tolerant capabilities.

### Key Features

- **Behavior Tree Integration**: Modular and extensible task execution framework using BehaviorTree.CPP.
- **ROS Navigation Interface**: Seamless integration with `move_base` for goal-based navigation.
- **Joystick-Controlled Chassis Movement**: Real-time chassis control using joystick input.
- **Custom Message/Service/Action Support**: Full support for custom-defined `.msg`, `.srv`, and `.action` files.
- **Real-Time Execution Logging**: Integrated logging system with configurable verbosity levels.
- **Visualization Support**: Optional integration with Groot for visual debugging of behavior trees.
- **Fault Tolerance**: Retry, timeout, and preemption mechanisms for robust execution.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

* [![C++][CPP]][CPP-url]
* [![ROS][ROS]][ROS-url]
* [![BehaviorTree.CPP][BT.CPP]][BT.CPP-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### 📁 Project Structure

<details>
<summary>Click to expand project structure</summary>

```
rc_decision/
├── .clang-format
├── .clang-tidy
├── .pre-commit-config.yaml
├── CMakeLists.txt
├── package.xml
├── action/
│   └── Fibonacci.action
├── image/
│   ├── 1.png
│   ├── 2.png
│   └── 3.png
├── include/
│   └── rc_decision/
│       ├── bt_action_node.h
│       ├── bt_service_node.h
│       ├── aurora/
│       │   ├── ChassisMove.h
│       │   ├── laser_goal.h
│       │   └── movebase_client.h
│       ├── blackboard/
│       │   ├── RosJoy.h
│       │   └── blackboard.h
│       └── loggers/
│           └── rosout_logger.h
├── launch/
│   ├── RosJoy.launch
│   └── control_loop.launch
├── msg/
│   ├── BehaviorTree.msg
│   ├── NodeParameter.msg
│   ├── NodeStatus.msg
│   ├── StatusChange.msg
│   ├── StatusChangeLog.msg
│   └── TreeNode.msg
├── src/
│   ├── ChassisMove.cpp
│   ├── control_loop.cpp
│   ├── laser_goal.cpp
│   ├── move_base_client.cpp
│   └── loggers/
│       └── rosout_logger.cpp
├── srv/
│   └── AddTwoInts.srv
└── test/
    ├── launch/
    │   ├── test_client.launch
    │   └── test_server.launch
    └── treeNode/
        ├── test_bt.cpp
        └── test_server.cpp
```

</details>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->

## 🚀 Getting Started

This is an example of how you may give instructions on setting up your project locally. To get a local copy up and running follow these simple steps.

### Prerequisites

- Ubuntu 18.04 or later
- ROS Melodic or Noetic installed
- catkin workspace configured
- C++14 compiler
- `behaviortree_cpp_v3` library installed

### Installation

1. Clone the repository into your catkin workspace:
   
   ```bash
   cd ~/catkin_ws/src
   git clone https://github.com/gdut-robocon/rc_decision.git
   ```
2. Build the package:
   
   ```bash
   cd ~/catkin_ws
   catkin_make
   ```
3. Source the workspace:
   
   ```bash
   source devel/setup.bash
   ```

### Configuration

- Ensure the ROS navigation stack is running and `move_base` is active.
- Configure joystick input via `RosJoy.launch`.
- Modify scaling parameters in `ChassisMove.cpp` or via ROS parameter server if needed.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->

## 💻 Usage

To start the main behavior tree execution loop:

```bash
roslaunch rc_decision control_loop.launch
```

To test behavior tree functionality with sample tasks:

```bash
rosrun rc_decision test_bt
```

To start the test server (provides Fibonacci action and AddTwoInts service):

```bash
rosrun rc_decision test_server
```

For joystick-controlled chassis movement:

```bash
roslaunch rc_decision RosJoy.launch
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ROADMAP -->

## 🗺️ Roadmap

- [ ] Add support for dynamic reconfiguration of behavior trees
- [ ] Integrate with SLAM for real-time mapping and navigation
- [ ] Implement more advanced error handling and recovery strategies
- [ ] Add support for more sensor types (LiDAR, IMU, etc.)
- [ ] Enhance visualization with full Groot integration

See the [open issues](https://github.com/gdut-robocon/rc_decision/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTRIBUTING -->

## 🤝 Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Top contributors:

<a href="https://github.com/gdut-robocon/rc_decision/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=gdut-robocon/rc_decision" alt="contrib.rocks image" />
</a>

<!-- LICENSE -->

## 🎗 License

Copyright © 2024-2025 [rc_decision][rc_decision]. <br />
Released under the [MIT][license-url] license.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->

## 📧 Contact

Email: jialonglongliu@gmail.com

Project Link: [https://github.com/gdut-robocon/rc_decision](https://github.com/gdut-robocon/rc_decision)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- REFERENCE LINKS -->

[rc_decision]: https://github.com/gdut-robocon/rc_decision
[ROS]: http://wiki.ros.org/
[ROS-url]: http://wiki.ros.org/
[BT.CPP]: https://www.behaviortree.dev/
[BT.CPP-url]: https://www.behaviortree.dev/
[CPP]: https://img.shields.io/badge/C++-00599C?style=flat-round&logo=cplusplus&logoColor=white
[CPP-url]: https://en.wikipedia.org/wiki/C%2B%2B

<!-- MARKDOWN LINKS & IMAGES -->

[contributors-shield]: https://img.shields.io/github/contributors/gdut-robocon/rc_decision.svg?style=flat-round
[contributors-url]: https://github.com/gdut-robocon/rc_decision/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/gdut-robocon/rc_decision.svg?style=flat-round
[forks-url]: https://github.com/gdut-robocon/rc_decision/network/members
[stars-shield]: https://img.shields.io/github/stars/gdut-robocon/rc_decision.svg?style=flat-round
[stars-url]: https://github.com/gdut-robocon/rc_decision/stargazers
[issues-shield]: https://img.shields.io/github/issues/gdut-robocon/rc_decision.svg?style=flat-round
[issues-url]: https://github.com/gdut-robocon/rc_decision/issues
[license-shield]: https://img.shields.io/github/license/gdut-robocon/rc_decision.svg?style=flat-round
[license-url]: https://github.com/gdut-robocon/rc_decision/blob/master/LICENSE.txt