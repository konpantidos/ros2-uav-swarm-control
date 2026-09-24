from setuptools import setup
import os
from glob import glob

package_name = 'swarm_sim'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        # Εγκατάσταση των launch, models και worlds
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
        (os.path.join('share', package_name, 'models'), glob('models/*.urdf')),
        (os.path.join('share', package_name, 'worlds'), glob('worlds/*.world')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Konstantinos',
    maintainer_email='kon.pantidos@gmail.com',
    description='Gazebo simulation environment for the UAV swarm',
    license='MIT',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [],
    },
)
