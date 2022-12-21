## Functionalities

    - What will your project do, precisely?
    The project will be about creating living beings namely plants and creatures (predators and preys). The latter, have brains (neural networks), that allow them to take decisions. All living beings have some particular characteristics that define their physical strength, their eyesight, their nutritional values (in case they are eaten).
    We also introduced a new type of object, that is, a barrier, that the user can put in the environment. Living beings cannot go through the barrier. This way we will be able to separate the environment and allow interaction only between some subset of beings. 
    These beings will then be able to reproduce. Reproduction entails some random changes in the brain and/or characteristics of the beings and allows evolution to take place.
    

## Deadlines and deliverables

    - What intermediate deadlines do you have, and what subset of functionalities will you deliver in each deadline?

    Try to plan different stages for your project and have intermediate results you can show for each stage. This exercise will help you focusing your efforts and minimize the risks of failure.
    
    1 - Have a window with beings that move and have a working neural network. 
    2 - Include more carachteristics to the brain of the creatures (like having specific nutritional values).
    3 - Include the barrier and allow parallel evolution. 

## Software Architecture

    - How are you sub-dividing your project?Which modules are you implementing?
    We have a frontend team that takes care of how the application looks and how the user can interact with it. In particular, we have a subteam that cares about the window and the buttons in it and another subteam that takes care of th visualisation of creatures. 
    The backend has a the role of coding the behaviour of the beings. In particular, a subteams codes the reproduction, another takes care of implementing the responses given by the brain and another one codes the neural network  itself.

    - What is the interface of each module?
      You can define the interface with the public section of your class headers (note that not all classes need to be "exposed" from one module to the others).

    - What external dependencies do you have? Why?
    We are using QtGraphicsLibrary in order to code the frontend and we coded our own neural network, therefore everything is integrated into the Qt environment. 
