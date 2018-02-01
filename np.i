[Mesh]
  type = GeneratedMesh
  dim = 1
  xmin = 0
  xmax = 0.000003 #meters
  nx = 100
[]


[Variables]

  [./potential]
    order = FIRST
    family = LAGRANGE
  [../]

  [./conA]
    order = FIRST
    family = LAGRANGE
  [../]

[]

# The Preconditioning block
[Preconditioning]
  active = 'mySMP'
  [./mySMP]
    type = SMP
    full = true 
  [../]
[]

[AuxVariables]
  [./flux_A]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Kernels]
  [./potential_diff]
    type = Diffusion
    variable = potential
  [../]

  [./potential_induced_A]
     type = Potential
     variable = potential
     concentration = conA
     permittivity = 449590000  #1/(4*pi*dielectric Zr*epsilon_o) Nm^2/C^2
     charge = -1
   [../]

  [./conA_diff]
    type = Diffusion
    variable = conA
  [../]

  [./conA_coupled]
    type = PNPConc
    variable = conA
    potential = potential
    mobility = -4.51328e-11  # cm^2/(V-S)
    gradchem = '0.0 0.0 0.0'
  [../]

[]

[AuxKernels]
  [./flux_A]
    type = Flux
    variable = flux_A
    concentration = conA
  [../]
 
[]



[BCs]
  [./potleft]
    type = DirichletBC
    variable = potential
    boundary = '0'
    value = 0
  [../]

  [./potright]
    type = DirichletBC
    variable = potential
    boundary = '1'
    value = 0
 [../]

  [./Aleft]
    type = DirichletBC
    variable = conA
    boundary = '10e17'
    value = 1
  [../]

  [./Aright]
    type = DirichletBC
    variable = conA
    boundary = '10e20'
    value = 0
 [../]

[]


#[UserObjects]
#  [./soln]
#    type = SolutionUserObject
#    system = nl0
#    mesh = pnp-restart_out_0005_mesh.xda
#    es = pnp-restart_out_0005.xda
#    system_variables = 'potential conA'
#    execute_on = initial
#  [../]
#[]



[Executioner]
  type = Steady
  solve_type = NEWTON
  #solve_type = PJFNK
  l_abs_step_tol = -1
  l_tol = 1.0e-5
  nl_rel_tol = 1.0e-3
  nl_max_its = 20
  l_max_its = 1000
  #petsc_options_iname = '-sub_pc_type'
  #petsc_options_value = '   hypre '
  #petsc_options_iname = '-pc_type -ksp_grmres_restart -sub_ksp_type -sub_pc_type -pc_asm_overlap'
  #petsc_options_value = 'asm      31                  preonly       lu           8'

  #petsc_options_iname = '-ksp_gmres_restart '
  #petsc_options_value = '300                '
  #line_search = 'none'
[]

[Debug]
  show_var_residual_norms = true
[]

[Outputs]
  exodus = true
 # checkpoint = true
 # xda = true
[]
